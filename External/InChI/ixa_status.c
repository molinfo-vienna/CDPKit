/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.07
 * April 30, 2024
 *
 * MIT License
 *
 * Copyright (c) 2024 IUPAC and InChI Trust
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*
* The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST.
 * Modifications and additions by IUPAC and the InChI Trust.
 * Some portions of code were developed/changed by external contributors
 * (either contractor or volunteer) which are listed in the file
 * 'External-contributors' included in this distribution.
 *
 * info@inchi-trust.org
 *
*/

#include <stdio.h> /* djb-rwth: required for vsnprintf */
/* int vsnprintf (char* s, size_t n, const char* format, va_list arg); */

#include "mode.h"
#include "inchi_api.h"
#include "bcf_s.h"
#include "ixa_status.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


#define MAXERR        50
#define MAX_MSGLENGTH 1024


typedef struct
{
    IXA_STATUS severity;
    char*      message;
} StatusItem;


typedef struct StatusBlockTag
{
    char                   data[MAX_MSGLENGTH];
    struct StatusBlockTag* next;
} StatusBlock;


typedef struct
{
    int          item_count;
    StatusItem   items[MAXERR];
    StatusBlock  first_block;
    StatusBlock* current_block;
    char*        current_position;
} INCHISTATUS;


static void BLOCK_clear( StatusBlock* pBlock )
{
    /* If the block points to yet another block, recursively clear the entire list.*/
    if (pBlock->next)
    {
        BLOCK_clear( pBlock->next );
        inchi_free( pBlock->next );
        pBlock->next = NULL;
    }
}


static void STATUS_init( INCHISTATUS* pStatus )
{
    pStatus->first_block.next = NULL;
    pStatus->current_block = &pStatus->first_block;
    pStatus->current_position = pStatus->current_block->data;
    pStatus->item_count = 0;
}


static void STATUS_Clear( INCHISTATUS* pStatus )
{
    BLOCK_clear( &pStatus->first_block );
    /* Fixed memory leak in original code */
    if (pStatus->item_count)
    {
        int i;
        for (i = 0; i < pStatus->item_count; i++)
        {
            if (pStatus->items[i].message)
            {
                inchi_free( pStatus->items[i].message );
                pStatus->items[i].message = NULL;
            }
        }
    }
    STATUS_init( pStatus );
}


/****************************************************************************/
IXA_STATUS_HANDLE STATUS_Pack( INCHISTATUS* pStatus )
{
    return (IXA_STATUS_HANDLE) pStatus;
}



/****************************************************************************/
static INCHISTATUS* STATUS_Unpack( IXA_STATUS_HANDLE hStatus )
{
    return (INCHISTATUS*) hStatus;
}


/****************************************************************************/
void STATUS_PushMessage( IXA_STATUS_HANDLE hStatus,
                         IXA_STATUS vSeverity,
                         char *pFormat,
                         ... )
{
    va_list     arguments;
    char        buffer[MAX_MSGLENGTH];
    StatusItem* item;
    int         item_index;
    int         size;

    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return;
    }

    if (!pFormat)
    {
        /* We shouldn't get here */
        return;
    }

    if (status->item_count < MAXERR)
    {
        /* The stack is not yet full. Push another item onto it. */
        item = &status->items[status->item_count];
        status->item_count++;
    }
    else
    {
        /* The stack is already full. Shuffle the existing items down to make room
        for the new one. The bottom-most item falls off the end and is lost. */
        for (item_index = 1; item_index < status->item_count; item_index++)
        {
            status->items[item_index - 1].severity = status->items[item_index].severity;
            status->items[item_index - 1].message = status->items[item_index].message;
        }
        item = &status->items[status->item_count - 1];
    }

    item->severity = vSeverity;

    /* Build the message string and write it to the new stack entry. */
    va_start( arguments, pFormat );
#if( defined( _WIN32 ) && defined( _MSC_VER ) && _MSC_VER <= 1200 )
    /* VC6 insists on having _vsnprintf */
    size = _vsnprintf( buffer, sizeof( buffer ), pFormat, arguments ) + 1;
#else
    size = vsnprintf( buffer, sizeof( buffer ), pFormat, arguments ) + 1;
#endif
    va_end( arguments );

/* vsnprintf returns -1 if it had to truncate the string, which shows
   up here as a size of zero. */
    if (size == 0)
    {
        buffer[sizeof( buffer ) - 4] = '.';
        buffer[sizeof( buffer ) - 3] = '.';
        buffer[sizeof( buffer ) - 2] = '.';
        buffer[sizeof( buffer ) - 1] = '\0';
        size = sizeof( buffer );
    }

    item->message = (char *) inchi_malloc( size );
    if (item->message)
    {
        strcpy( item->message, buffer );
    }
}


/****************************************************************************/
static IXA_BOOL INCHISTATUS_TestSeverity( IXA_STATUS_HANDLE hStatus,
                                          IXA_STATUS vSeverity )
{
    int item_index;

    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return IXA_FALSE;
    }
    for (item_index = 0; item_index < status->item_count; item_index++)
    {
        if (status->items[item_index].severity == vSeverity)
        {
            return IXA_TRUE;
        }
    }
    return IXA_FALSE;
}


/****************************************************************************/
IXA_STATUS_HANDLE INCHI_DECL IXA_STATUS_Create( void )
{
    INCHISTATUS* status = (INCHISTATUS*) inchi_malloc( sizeof( INCHISTATUS ) );
    if (!status)
    {
        return NULL;
    }
    STATUS_init( status );
    return STATUS_Pack( status );
}


/****************************************************************************/
void INCHI_DECL IXA_STATUS_Destroy( IXA_STATUS_HANDLE hStatus )
{
    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return;
    }
    STATUS_Clear( status );
    inchi_free( status );
}


/****************************************************************************/
void INCHI_DECL IXA_STATUS_Clear( IXA_STATUS_HANDLE hStatus )
{
    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return;
    }
    STATUS_Clear( status );
}


/****************************************************************************/
IXA_BOOL INCHI_DECL IXA_STATUS_HasError( IXA_STATUS_HANDLE hStatus )
{
    return INCHISTATUS_TestSeverity( hStatus, IXA_STATUS_ERROR );
}


/****************************************************************************/
IXA_BOOL INCHI_DECL IXA_STATUS_HasWarning( IXA_STATUS_HANDLE hStatus )
{
    return INCHISTATUS_TestSeverity( hStatus, IXA_STATUS_WARNING );
}


/****************************************************************************/
int INCHI_DECL IXA_STATUS_GetCount( IXA_STATUS_HANDLE hStatus )
{
    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return 0;
    }

    return status->item_count;
}


/****************************************************************************/
const char* INCHI_DECL IXA_STATUS_GetMessage( IXA_STATUS_HANDLE hStatus,
                                              int               vIndex )
{
    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return "Invalid status handle";
    }
    if (( vIndex < 0 ) || ( vIndex >= status->item_count ))
    {
        return "Message index is out of range";
    }

    return status->items[vIndex].message;
}


/****************************************************************************/
IXA_STATUS INCHI_DECL IXA_STATUS_GetSeverity( IXA_STATUS_HANDLE hStatus,
                                              int               vIndex )
{
    INCHISTATUS* status = STATUS_Unpack( hStatus );
    if (!status)
    {
        return IXA_STATUS_ERROR;
    }
    if (( vIndex < 0 ) || ( vIndex >= status->item_count ))
    {
        return IXA_STATUS_ERROR;
    }

    return status->items[vIndex].severity;
}
