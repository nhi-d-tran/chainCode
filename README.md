# chainCode

I. Input (use argv[]): a binary image contain only one object without hole.

II. Outputs: You should have two output files:

- outFile1: it is for storing the chain-code of the object for future image decompression.

Output format:

#rows #cols min max // image header use one text line

Label startRow startCol code1 code2 code3 ....

- outFile2: it is for debugging and for printing the chain code:

#rows #cols min max // one text line

startRow startCol Label // one text line

code1 code2 code3 
....


*******************************
III. Data structure:
*******************************
- An image class
- numRows (int)
- numCols (int)
- minVal (int)
- maxVal (int)
- imgAry (int **) a 2D array to store the input image,

methods:
- constructor(s)

- loadImage () // Read from the input label file onto imageAry begin at (1,1)

- zeroFramed ()

- a chainCode class

- a Point class
row (int)
col (int)

- neighborCoord[8] (Point)
- startP (point) // the x-y coordinate of the first pixel of the object.
- currentP (Point) // current none zero border pixel
- nextP (Point) // next none zero border neighbor pixel
- lastQ (int) // Range from 0 to 7, it is the direction of
- nextQ (int)
- nextDirTable[8] 
- nextDir (int)
- PchainDir // chain code direction from currentP to nextP

methods:
- constructors
- getChainCode()
- loadNeighborsCoord(...)
- findNextP (...)
- getChainDir(currentP, nextQ) 
- prettyPrint

*******************************
III. In Main
*******************************
step 1: inFile <- open the input file, argv[1]

             open outFile1 and outFile2
            
             read image header from inFile
            
             output the image header to outFile1
            
             output image header to outFile2 // per text line
            
step 2: imgAry <- dynamically allocated

step 3: loadImage()

step 4: zeroFramed ()

step 5: getChainCode()

step 6: close all files
