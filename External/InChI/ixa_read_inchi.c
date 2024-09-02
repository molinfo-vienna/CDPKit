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


#include "string.h"

#include "mode.h"
#include "inchi_api.h"
#include "util.h"
#include "bcf_s.h"
#include "ixa_mol.h"
#include "ixa_status.h"



/****************************************************************************/
static IXA_ATOMID AnalyseInternalVertex( IXA_STATUS_HANDLE hStatus,
                                         IXA_MOL_HANDLE hMolecule,
                                         IXA_ATOMID vVertex,
                                         IXA_ATOMID vInternal,
                                         IXA_ATOMID vIgnore1,
                                         IXA_ATOMID vIgnore2 )
{
    int        bond_count;
    int        bond_index;
    IXA_BONDID bond;
    IXA_ATOMID nbr;

    bond_count = IXA_MOL_GetAtomNumBonds( hStatus, hMolecule, vInternal );
    if (IXA_STATUS_HasError( hStatus ))
    {
        return IXA_ATOMID_INVALID;
    }
    switch (bond_count)
    {
        case 2:
            /* One bond joins vInternal to vVertex. The other joins vInternal to the
               distal part of the stereo centre. No other bonds are available so we
               presume that the vertex we are looking for is an implicit hydrogen. */
            return IXA_ATOMID_IMPLICIT_H;

        case 3:
            /* Look for a neighbour of vInternal which is not any of the ones whose role
               has already been accounted for. Assume that any such neighbour is a previously
               unidentified vertex of the stereo centre. */
            for (bond_index = 0; bond_index < bond_count; bond_index++)
            {
                bond = IXA_MOL_GetAtomBond( hStatus, hMolecule, vInternal, bond_index );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    return IXA_ATOMID_INVALID;
                }
                nbr = MOL_GetBondOtherAtom( hStatus, hMolecule, bond, vInternal );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    return IXA_ATOMID_INVALID;
                }
                if (( nbr != vVertex ) && ( nbr != vIgnore1 ) && ( nbr != vIgnore2 ))
                {
                    return nbr;
                }
            }
            STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Illegal rectangular centre detected" );
            return IXA_ATOMID_INVALID;

        default:
            STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Illegal rectangular centre detected" );
            return IXA_ATOMID_INVALID;
    }
}


/****************************************************************************/
static IXA_BONDID FindCumuleneCentre( IXA_STATUS_HANDLE hStatus,
                                      IXA_MOL_HANDLE hMolecule,
                                      IXA_ATOMID vInternal1,
                                      IXA_ATOMID vInternal2 )
{
    int              bond_count1;
    int              bond_index1;
    IXA_BONDID   bond1;
    IXA_ATOMID   atom1;
    int              bond_count2;
    int              bond_index2;
    IXA_BONDID   bond2;
    IXA_ATOMID   atom2;
    IXA_BONDID   central_bond;
    IXA_BOND_TYPE type;

    bond_count1 = IXA_MOL_GetAtomNumBonds( hStatus, hMolecule, vInternal1 );
    if (IXA_STATUS_HasError( hStatus ))
    {
        return IXA_BONDID_INVALID;
    }
    bond_count2 = IXA_MOL_GetAtomNumBonds( hStatus, hMolecule, vInternal2 );
    if (IXA_STATUS_HasError( hStatus ))
    {
        return IXA_BONDID_INVALID;
    }

    for (bond_index1 = 0; bond_index1 < bond_count1; bond_index1++)
    {
        bond1 = IXA_MOL_GetAtomBond( hStatus, hMolecule, vInternal1, bond_index1 );
        if (IXA_STATUS_HasError( hStatus ))
        {
            return IXA_BONDID_INVALID;
        }
        atom1 = MOL_GetBondOtherAtom( hStatus, hMolecule, bond1, vInternal1 );
        if (IXA_STATUS_HasError( hStatus )) return IXA_BONDID_INVALID;
        for (bond_index2 = 0; bond_index2 < bond_count2; bond_index2++)
        {
            bond2 = IXA_MOL_GetAtomBond( hStatus, hMolecule, vInternal2, bond_index2 );
            if (IXA_STATUS_HasError( hStatus ))
            {
                return IXA_BONDID_INVALID;
            }
            atom2 = MOL_GetBondOtherAtom( hStatus, hMolecule, bond2, vInternal2 );
            if (IXA_STATUS_HasError( hStatus ))
            {
                return IXA_BONDID_INVALID;
            }
            central_bond = IXA_MOL_GetCommonBond( hStatus, hMolecule, atom1, atom2 );
            if (IXA_STATUS_HasError(hStatus))
            {
                return IXA_BONDID_INVALID;
            }
            if (central_bond != IXA_BONDID_INVALID)
            {
                type = IXA_MOL_GetBondType( hStatus, hMolecule, central_bond );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    return IXA_BONDID_INVALID;
                }
                if (type != IXA_BOND_TYPE_DOUBLE)
                {
                    STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Central bond of cumulene must be double" );
                    return IXA_BONDID_INVALID;
                }
                return central_bond;
            }
        }
    }

    STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Cannot find central bond for cumulene" );

    return IXA_BONDID_INVALID;
}


/****************************************************************************/
void INCHI_DECL IXA_MOL_ReadInChI( IXA_STATUS_HANDLE hStatus,
                                   IXA_MOL_HANDLE    hMolecule,
                                   const char*       pInChI )
{
    inchi_InputINCHI        input;
#ifdef IXA_USES_NON_EX_CORE_API
    inchi_OutputStruct        output;
#else
    inchi_OutputStructEx    output;
#endif
    int                atom_index;
    IXA_ATOMID         atom;
    int                bond_count;
    int                bond_index;
    IXA_BONDID         bond;
    int                nbr_index;
    IXA_ATOMID         nbr;
    int                direction;
    int                stereo_index;
    IXA_STEREOID       stereo;
    int res;

    IXA_MOL_Clear( hStatus, hMolecule );
    if (IXA_STATUS_HasError( hStatus ))
    {
        goto cleanup;
    }

    input.szInChI = (char*) pInChI;
    input.szOptions = "";

#ifdef IXA_USES_NON_EX_CORE_API
    res = GetStructFromINCHI( &input, &output );
#else
    res = GetStructFromINCHIEx( &input, &output );
#endif
    if (res == inchi_Ret_ERROR || res == inchi_Ret_FATAL)
    {
        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, output.szMessage );
        goto cleanup;
    }
    else if (res == inchi_Ret_WARNING)
    {
        STATUS_PushMessage( hStatus, IXA_STATUS_WARNING, output.szMessage );
    }


#ifndef IXA_USES_NON_EX_CORE_API
        /* Check for and then replace star atoms if Polymer extension is supplied */
    if (output.polymer && output.polymer->n && output.polymer->units && output.polymer->units[0])
    {
        for (atom_index = 0; atom_index < output.num_atoms; atom_index++)
        {
            if (!strcmp( output.atom[atom_index].elname, "*" ))
            {
                strcpy( output.atom[atom_index].elname, "Zz" );
            }
        }
    }
#endif

    for (atom_index = 0; atom_index < output.num_atoms; atom_index++)
    {
        int mass;
        if (( ISOTOPIC_SHIFT_FLAG - ISOTOPIC_SHIFT_MAX <= output.atom[atom_index].isotopic_mass ) &&
            ( output.atom[atom_index].isotopic_mass <= ISOTOPIC_SHIFT_FLAG + ISOTOPIC_SHIFT_MAX ))
        {
            int base_mass = get_atomic_mass( output.atom[atom_index].elname );
            mass = base_mass + output.atom[atom_index].isotopic_mass - ISOTOPIC_SHIFT_FLAG;
        }
        else
        {
            mass = output.atom[atom_index].isotopic_mass;
        }
        atom = IXA_MOL_CreateAtom( hStatus, hMolecule );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomElement( hStatus, hMolecule, atom, output.atom[atom_index].elname );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomCharge( hStatus, hMolecule, atom, output.atom[atom_index].charge );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomRadical( hStatus, hMolecule, atom, (IXA_ATOM_RADICAL) output.atom[atom_index].radical );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomMass( hStatus, hMolecule, atom, mass );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomHydrogens( hStatus, hMolecule, atom, 0, output.atom[atom_index].num_iso_H[0] );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomHydrogens( hStatus, hMolecule, atom, 1, output.atom[atom_index].num_iso_H[1] );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomHydrogens( hStatus, hMolecule, atom, 2, output.atom[atom_index].num_iso_H[2] );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomHydrogens( hStatus, hMolecule, atom, 3, output.atom[atom_index].num_iso_H[3] );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomX( hStatus, hMolecule, atom, output.atom[atom_index].x );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomY( hStatus, hMolecule, atom, output.atom[atom_index].y );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        IXA_MOL_SetAtomZ( hStatus, hMolecule, atom, output.atom[atom_index].z );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
    }

    for (atom_index = 0; atom_index < output.num_atoms; atom_index++)
    {
        atom = IXA_MOL_GetAtomId( hStatus, hMolecule, atom_index );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
        for (bond_index = 0; bond_index < output.atom[atom_index].num_bonds; bond_index++)
        {
            nbr_index = output.atom[atom_index].neighbor[bond_index];
            if (nbr_index > atom_index)
            {
                nbr = IXA_MOL_GetAtomId( hStatus, hMolecule, nbr_index );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                bond = IXA_MOL_CreateBond( hStatus, hMolecule, atom, nbr );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                IXA_MOL_SetBondType( hStatus, hMolecule, bond, (IXA_BOND_TYPE) output.atom[atom_index].bond_type[bond_index] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }

                direction = output.atom[atom_index].bond_stereo[bond_index] & 0x08;
                switch (direction)
                {
                    case INCHI_BOND_STEREO_NONE:
                        break;
                    case INCHI_BOND_STEREO_SINGLE_1UP:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, atom, IXA_BOND_WEDGE_UP );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_SINGLE_1EITHER:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, atom, IXA_BOND_WEDGE_EITHER );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_SINGLE_1DOWN:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, atom, IXA_BOND_WEDGE_DOWN );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_SINGLE_2UP:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, nbr, IXA_BOND_WEDGE_UP );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_SINGLE_2EITHER:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, nbr, IXA_BOND_WEDGE_EITHER );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_SINGLE_2DOWN:
                        IXA_MOL_SetBondWedge( hStatus, hMolecule, bond, nbr, IXA_BOND_WEDGE_DOWN );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    case INCHI_BOND_STEREO_DOUBLE_EITHER:
                        IXA_MOL_SetDblBondConfig( hStatus, hMolecule, bond, IXA_DBLBOND_CONFIG_EITHER );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        break;
                    default:
                        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Stereo code %d is not recognised", direction );
                        goto cleanup;
                }
            }
        }
    }

    for (stereo_index = 0; stereo_index < output.num_stereo0D; stereo_index++)
    {
        switch (output.stereo0D[stereo_index].type)
        {
            case INCHI_StereoType_Tetrahedral:
            {
                atom = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].central_atom );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                bond_count = IXA_MOL_GetAtomNumBonds( hStatus, hMolecule, atom );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                switch (bond_count)
                {
                    case 3:
                    {
                        IXA_ATOMID nbr1;
                        IXA_ATOMID nbr2;
                        IXA_ATOMID nbr3;

                        nbr1 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[1] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        nbr2 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[2] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        nbr3 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[3] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }

                        stereo = IXA_MOL_CreateStereoTetrahedron( hStatus, hMolecule,
                            atom, IXA_ATOMID_IMPLICIT_H, nbr1, nbr2, nbr3 );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                    }
                    break;

                    case 4:
                    {
                        IXA_ATOMID nbr0;
                        IXA_ATOMID nbr1;
                        IXA_ATOMID nbr2;
                        IXA_ATOMID nbr3;

                        nbr0 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[0] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        nbr1 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[1] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        nbr2 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[2] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        nbr3 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[3] );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                        stereo = IXA_MOL_CreateStereoTetrahedron( hStatus, hMolecule,
                            atom, nbr0, nbr1, nbr2, nbr3 );
                        if (IXA_STATUS_HasError( hStatus ))
                        {
                            goto cleanup;
                        }
                    } break;

                    default:
                        STATUS_PushMessage( hStatus, IXA_STATUS_ERROR,
                            "Central atom of tetrahedral centre must have 3 or 4 neighbours" );
                        goto cleanup;
                }
            } break;

            case INCHI_StereoType_DoubleBond:
            {
                IXA_ATOMID nbr1a;
                IXA_ATOMID nbr1b;
                IXA_ATOMID internal1;
                IXA_ATOMID nbr2a;
                IXA_ATOMID nbr2b;
                IXA_ATOMID internal2;
                IXA_BONDID central_bond;

                nbr1a = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[0] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                nbr2b = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[3] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }

                internal1 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[1] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                internal2 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[2] );
                if (IXA_STATUS_HasError( hStatus )) goto cleanup;
                central_bond = IXA_MOL_GetCommonBond( hStatus, hMolecule, internal1, internal2 );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                if (central_bond != IXA_BONDID_INVALID)
                {
                    /* The stereo centre is an olefin. */
                    nbr1b = AnalyseInternalVertex( hStatus, hMolecule, nbr1a, internal1, internal2, IXA_ATOMID_INVALID );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }

                    nbr2a = AnalyseInternalVertex( hStatus, hMolecule, nbr2b, internal2, internal1, IXA_ATOMID_INVALID );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                }
                else
                {
                    IXA_ATOMID central1;
                    IXA_ATOMID central2;

                    /* The stereo centre is not an olefin. Assume it is a cumulene. */
                    central_bond = FindCumuleneCentre( hStatus, hMolecule, internal1, internal2 );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                    central1 = IXA_MOL_GetBondAtom1( hStatus, hMolecule, central_bond );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                    central2 = IXA_MOL_GetBondAtom2( hStatus, hMolecule, central_bond );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                    nbr1b = AnalyseInternalVertex( hStatus, hMolecule, nbr1a, internal1, central1, central2 );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                    nbr2a = AnalyseInternalVertex( hStatus, hMolecule, nbr2b, internal2, central1, central2 );
                    if (IXA_STATUS_HasError( hStatus ))
                    {
                        goto cleanup;
                    }
                }

                stereo = IXA_MOL_CreateStereoRectangle( hStatus, hMolecule,
                    central_bond, nbr1a, nbr1b, nbr2a, nbr2b );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
            }
            break;

            case INCHI_StereoType_Allene:
            {
                IXA_ATOMID nbr1a;
                IXA_ATOMID nbr1b;
                IXA_ATOMID internal1;
                IXA_ATOMID nbr2a;
                IXA_ATOMID nbr2b;
                IXA_ATOMID internal2;
                IXA_ATOMID central_atom;

                nbr1a = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[0] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                nbr2b = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[3] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                internal1 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[1] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                internal2 = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].neighbor[2] );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                central_atom = IXA_MOL_GetAtomId( hStatus, hMolecule, output.stereo0D[stereo_index].central_atom );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                nbr1b = AnalyseInternalVertex( hStatus, hMolecule, nbr1a, internal1, central_atom, IXA_ATOMID_INVALID );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
                nbr2a = AnalyseInternalVertex( hStatus, hMolecule, nbr2b, internal2, central_atom, IXA_ATOMID_INVALID );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }

                stereo = IXA_MOL_CreateStereoAntiRectangle( hStatus, hMolecule,
                    central_atom, nbr1a, nbr1b, nbr2a, nbr2b );
                if (IXA_STATUS_HasError( hStatus ))
                {
                    goto cleanup;
                }
            } break;

            default:
                STATUS_PushMessage( hStatus, IXA_STATUS_ERROR,
                    "Stereo type %d is not recognised", output.stereo0D[stereo_index].type );
                goto cleanup;
        }

        IXA_MOL_SetStereoParity( hStatus, hMolecule, stereo, (IXA_STEREO_PARITY) output.stereo0D[stereo_index].parity );
        if (IXA_STATUS_HasError( hStatus ))
        {
            goto cleanup;
        }
    }

#ifdef IXA_USES_NON_EX_CORE_API
#else
    /* v. 1.5 extensions */
    {
        res = IXA_MOL_SetExtMolDataByInChIExtInput( hStatus, hMolecule, output.polymer, output.v3000, output.num_atoms );
        if (res)
        {
            STATUS_PushMessage( hStatus, IXA_STATUS_ERROR, "Error creating IXA molecule by read InChI string" );
            goto cleanup;
        }
    }
#endif

cleanup:
#ifdef IXA_USES_NON_EX_CORE_API
    FreeStructFromINCHI( &output );
#else
    FreeStructFromINCHIEx( &output );
#endif
}
