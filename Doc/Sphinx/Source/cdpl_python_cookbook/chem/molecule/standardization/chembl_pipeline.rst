ChEMBL Structure Curation Pipeline
==================================

The script *chembl_preproc.py* Performs molecule standardization according to the ChEMBL structure
curation pipeline workflow :cite:`Bento2020`.

**Synopsis**

  :program:`python` *chembl_preproc.py* [-h] -i <file> -o <file> [-v <0|1|2>] [-p <true|false>] [-d] [-x <true|false>]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Output molecule file
  
**Other options**

 -h, --help

    Show help message and exit

 -i <file>

    Input molecule file

 -o <file>

    Output molecule file

 -v <0|1|2>

    Verbosity level (default: 1; 0 -> no console output, 1 -> verbose, 2 -> extra verbose)

 -p <true|false>

    Extract parent structure (default: true)

 -d

    Drop structures that fulfill the exclusion criterions (default: false)

 -x <true|false>

    Standardize structures that fulfill the exclusion criterions (default: true)
  
**Code**

.. literalinclude:: /downloads/chembl_preproc.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/chembl_preproc.py>`
