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


#ifndef __INCHI_DLL_B_H__
#define __INCHI_DLL_B_H__

#ifndef AB_PARITY_UNKN
#define AB_PARITY_UNKN   3  /* 3 => user marked as unknown parity */
#endif
#ifndef AB_PARITY_UNDF
#define AB_PARITY_UNDF   4  /* 4 => parity cannot be defined because of symmetry or not well defined geometry */
#endif


#define MOL2INCHI_NO_RAM    1001
#define MOL2INCHI_BAD_COMMAND_LINE 1002


void FreeInchi_Stereo0D( inchi_Stereo0D **stereo0D );
void FreeInchi_Atom( inchi_Atom **at );
inchi_Atom *CreateInchiAtom( int num_atoms );
inchi_Stereo0D *CreateInchi_Stereo0D( int num_stereo0D );
void FreeInchi_Input( inchi_Input *inp_at_data );
S_SHORT *is_in_the_slist( S_SHORT *pathAtom, S_SHORT nNextAtom, int nPathLen );
int is_element_a_metal( char szEl[] );

int InchiToInchiAtom( INCHI_IOSTREAM *inp_molfile,
                      inchi_Stereo0D **stereo0D,
                      int *num_stereo0D,
                      int bDoNotAddH,
                      int vABParityUnknown,
                      INPUT_TYPE nInputType,
                      inchi_Atom **at,
                      int max_num_at,
                      int *num_dimensions,
                      int *num_bonds,
                      char *pSdfLabel,
                      char *pSdfValue,
                      long *Id,
                      INCHI_MODE *pInpAtomFlags,
                      int *err,
                      char *pStrErr );


#endif /* __INCHI_DLL_B_H__ */
