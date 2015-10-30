#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <WProtectConfig.h>

long m_random()
{
  //  srand( time( NULL ) );
  long r;
  if ( sizeof( long ) == 8 )
  {
    r = rand( );
    r = r << 32;
    r = r | rand(  );      
  }
  else
  {
    r = rand( );
  }
  return r;
}


/*
long m_random(long max_size)
{
  srand( time( NULL ) );
  long r;
  if (sizeof( long ) == 8 )
  {
    long t = max_size;
    t = t>>32;
    r = rand(  )%t;
    r = r << 32;
    r = r | rand(  );
  }
  else {
    r = rand( )%max_size;
  }
  return r;
}*/
