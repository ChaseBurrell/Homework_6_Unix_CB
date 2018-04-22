/*
 * Usage of CDK Matrix
 *
 * Name: Chase Burrell 
 * NetID: cab160330
 * Email: cab160330@utdallas.edu 
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <cstring>
#include <sstream>


#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader {
public: 

	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord {
public: 
	uint8_t strLength; 
	char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
 
  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

/*Read in the binary file*/
 BinaryFileHeader *myHeader = new BinaryFileHeader();
 ifstream binInFile ("cs3377.bin", ios::in | ios::binary);
 binInFile.read((char *) myHeader, sizeof(BinaryFileHeader));

 /*Display the hex value for Magic Number*/
 stringstream stream;
 stream << uppercase <<  hex << myHeader->magicNumber;
 string result(stream.str());
 setCDKMatrixCell(myMatrix, 1, 1, string( "Magic: " + string( "0x") +  string(result.c_str())).c_str());
 drawCDKMatrix(myMatrix, true);

 /*Display version number*/
 stream.str("");
 stream << dec << myHeader->versionNumber;
 result = stream.str();
 setCDKMatrixCell(myMatrix, 1, 2, string( "Version: " +  string(result.c_str())).c_str());

 /*Display number of records*/
  stream.str("");
  stream << dec << myHeader->numRecords;
  result = stream.str();
  setCDKMatrixCell(myMatrix, 1, 3, string( "NumRecords: " +  string(result.c_str())).c_str());

 /*Display up to 4 records*/
 stream.str("");
 BinaryFileRecord *myRecord = new BinaryFileRecord();
 /*Loop to display up to 4 records*/
 for(int i = 2; i < 6; i ++) { 
 	binInFile.read((char *) myRecord, sizeof(BinaryFileRecord));
 	if(binInFile) {
 		result = to_string(myRecord->strLength);
 		setCDKMatrixCell(myMatrix, i, 1, string("strlen: " + result).c_str());
 		result = myRecord->stringBuffer;
 		setCDKMatrixCell(myMatrix, i, 2, result.c_str());
 		continue;
 	}
 	else {
  		i = 6;
  		continue;
  	}
 }


  /*
   * Dipslay a message
   */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
