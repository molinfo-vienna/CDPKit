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


#include "mode.h"
#include "inchi_api.h"
#include "bcf_s.h"
#include "ixa_status.h"
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char* inchi;
    char  inchi_key[256];
    int   dirty;
} INCHIKEYBUILDER;


/****************************************************************************/
static INCHIKEYBUILDER* KEYBUILDER_Unpack( IXA_STATUS_HANDLE hStatus,
                                           IXA_INCHIKEYBUILDER_HANDLE hKeyBuilder )
{
    if (!hKeyBuilder)
    {
        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Illegal keybuilder handle detected" );
        return NULL;
    }

    return (INCHIKEYBUILDER*) hKeyBuilder;
}


/****************************************************************************/
static IXA_INCHIKEYBUILDER_HANDLE KEYBUILDER_Pack( INCHIKEYBUILDER *pKeyBuilder )
{
    return (IXA_INCHIKEYBUILDER_HANDLE) pKeyBuilder;
}


/****************************************************************************/
IXA_INCHIKEYBUILDER_HANDLE INCHI_DECL IXA_INCHIKEYBUILDER_Create( IXA_STATUS_HANDLE hStatus )
{
    INCHIKEYBUILDER* key_builder = (INCHIKEYBUILDER*) inchi_malloc( sizeof( INCHIKEYBUILDER ) );
    if (!key_builder)
    {
        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Out of memory" );
        return NULL;
    }

    memset( key_builder, 0, sizeof( INCHIKEYBUILDER ) ); /* djb-rwth: memset_s C11/Annex K variant? */
    return KEYBUILDER_Pack( key_builder );
}


/****************************************************************************/
void INCHI_DECL IXA_INCHIKEYBUILDER_Destroy( IXA_STATUS_HANDLE hStatus,
                                             IXA_INCHIKEYBUILDER_HANDLE hKeyBuilder )
{
    INCHIKEYBUILDER* key_builder = KEYBUILDER_Unpack( hStatus, hKeyBuilder );
    if (!key_builder) return;

    inchi_free( key_builder->inchi );
    inchi_free( key_builder );
}


/****************************************************************************/
void INCHI_DECL IXA_INCHIKEYBUILDER_SetInChI( IXA_STATUS_HANDLE hStatus,
                                              IXA_INCHIKEYBUILDER_HANDLE hKeyBuilder,
                                              const char *pInChI )
{
    INCHIKEYBUILDER* key_builder = KEYBUILDER_Unpack( hStatus, hKeyBuilder );
    if (!key_builder)
    {
        return;
    }

    inchi_free( key_builder->inchi );
    key_builder->inchi = (char *) inchi_malloc( strlen( pInChI ) + 1 );
    if (!key_builder->inchi)
    {
        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Out of memory" );
        return;
    }

    strcpy( key_builder->inchi, pInChI );
    key_builder->dirty = 1;
}


/****************************************************************************/
const char* INCHI_DECL IXA_INCHIKEYBUILDER_GetInChIKey( IXA_STATUS_HANDLE hStatus,
                                                        IXA_INCHIKEYBUILDER_HANDLE hKeyBuilder )
{
    INCHIKEYBUILDER* key_builder = KEYBUILDER_Unpack( hStatus, hKeyBuilder );
    if (!key_builder) return NULL;

    if (key_builder->dirty)
    {
        char extra1[256];
        char extra2[256];
        if (GetINCHIKeyFromINCHI( key_builder->inchi, 0, 0, key_builder->inchi_key, extra1, extra2 ) != INCHIKEY_OK)
        {
            printf( "Failed to create InChIKey\n" );
            return NULL;
        }
        key_builder->dirty = 0;
    }

    return key_builder->inchi_key;
}
