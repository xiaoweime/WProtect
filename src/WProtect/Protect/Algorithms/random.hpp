/*
 *
 *   Copyright (C) Mon Jun 24 23:37:11 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _RANDOM_H_
#define _RANDOM_H_

long m_random();

class RandomEngender{
        int m;
        int b;
        int c;
        int d;
     public:  
        RandomEngender(){
            //long b,c,m;
            int count;
            int i;
            m=32767;
            b=gcd(m);
            c=5001;  
            d = 1;
        }
        RandomEngender(int _d){
            //long b,c,m;
            int count;
            int i;
            m=32767;
            b=gcd(m);
            c=5001;  
            d = _d;
        }
        ~RandomEngender(){

        }
        long My_Rand(long b,long c,long m)
        {
            return d=(b*d+c)%m;/*产生随机数，并记录，用来产生下一个伪随机数*/
        }
        long gcd1(long m,long n)
        {/*求最大公约数，算法中的b和m一般取互素*/
            long r;
            while((r=m%n)!=0)
            {
                m=n;
                n=r;
            }
            return n;
        }
        long gcd(long m)
        {/*计算与m互素的b*/
            long i=2;
            while(gcd1(i,m)!=1)
                i++;
            return i;
        }
        void randomseed(int _d)
        {
            d=_d;
        }
        long random()
        {
            return My_Rand(b,c,m);
        }
};
#endif /* _RANDOM_H_ */

//long m_random(long n); //获取多少以内的随机数
