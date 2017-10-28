//---------------------------------------------------------------------------
// wzByte.h
// Author       : Park Dong Ro
// LastModify   : 2003.11
// Comment      :
//---------------------------------------------------------------------------
#ifndef _WZ_BYTE_H_
#define _WZ_BYTE_H_
//---------------------------------------------------------------------------

/*
//----------------------------------------------------------------------------
class Byte
{
	
private:
public:
    Byte();
*/    
	short  getInt2( const unsigned char* b, int off);
	void   setInt2( unsigned char* b, int off, short int v);
	short  getLtInt2( const unsigned char* b, int off);
	void   setLtInt2( unsigned char* b, int off, short int v);
	unsigned short getUInt2( const unsigned char* b, int off);
	void   setUInt2( unsigned char* b, int off, unsigned short int v);
	unsigned short getLtUInt2( const unsigned char* b, int off);
	void   setLtUInt2( unsigned char* b, int off, unsigned short int v);

	unsigned int getUInt4( const unsigned char* b, int off);
	void   setUInt4( unsigned char* b, int off, unsigned int v);
	unsigned int getLtUInt4( const unsigned char* b, int off);
	void   setLtUInt4( unsigned char* b, int off, unsigned int v);
	int    getInt4( const unsigned char* b, int off);
	void   setInt4( unsigned char* b, int off, int v);
	int    getLtInt4( const unsigned char* b, int off);
	void   setLtInt4( unsigned char* b, int off, int v);

	float  getFloat( const unsigned char* b, int off);
	void   setFloat( unsigned char* b, int off, float v);
	double getDouble( const unsigned char* b, int off);
	void   setDouble( unsigned char* b, int off, double v);

    void   setTime4( unsigned char* b,   int off,
                     unsigned char year, unsigned char mon, unsigned char day,
                     unsigned char hour, unsigned char min, unsigned char sec );

	void   getTime4( const unsigned char* b, int off,
                     unsigned char *year, unsigned char *mon, unsigned char *day,
                     unsigned char *hour, unsigned char *min, unsigned char *sec);
                     
	#ifdef TARGET_ARM
	double ENDIAN_SWAP64(double v);
	#endif

    double get_WGP( const unsigned char* b, int off );
    void set_WGP( unsigned char* b, int off, double v );

	int strToHexStr(const unsigned char *str, int len, char *strHex);
	void dump(const unsigned char *buf, int len);
	
//};
//----------------------------------------------------------------------------

#endif

