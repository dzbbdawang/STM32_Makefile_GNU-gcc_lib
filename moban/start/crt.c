/****************************************************************************
*  Copyright (c) 2011 by Michael Fischer. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.
*
****************************************************************************
*  History:
*
*  09.04.2011  mifi  First Version
*  29.04.2011  mifi  Call SystemInit, and set the Vector Table Offset
*                    before copy of data and bss segment.
****************************************************************************/
#define __CRT_C__

#include <stdint.h>

/*=========================================================================*/
/*  DEFINE: All extern Data                                                */
/*=========================================================================*/
/*
 * The next data are defined by the linker script.
 */
extern unsigned long _stext;// 代码段起始地址
extern unsigned long _etext;// 代码段结束地址
extern unsigned long _sdata;// 数据段起始地址
extern unsigned long _edata;// 数据段结束地址
extern unsigned long _sbss;// BSS段起始地址
extern unsigned long _ebss;// BSS段结束地址
extern unsigned long _estack;// 堆栈起始地址

/* This is the main */
extern int main (void);

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/
void SystemInit (void) __attribute__((weak));

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/

/***************************************************************************/
 // Start of Selection
 /*  SystemInit                                                             */
 /*                                                                         */
 /*  SystemInit 是 CMSIS 接口提供的一个函数。                                 */
 /*  如果此函数不可用，我们需要在这里提供一个函数以防止                   */
 /*  链接器错误。 因此，这个函数被声明为弱符号。                            */
 /***************************************************************************/
void SystemInit (void)
{
} /* SystemInit */

/***************************************************************************/
/*  ResetHandler                                                           */
/*                                                                         */
/*  This function is used for the C runtime initialisation,                */
/*  for handling the .data and .bss segments.                              */
/***************************************************************************/
void Reset_Handler (void)
{
   uint32_t *pSrc;
   uint32_t *pDest;
   
   /*
    * 调用CMSIS接口中的SystemInit代码（如果可用）。
    * SystemInit是一个弱函数，可以被外部函数覆盖。
    */
   SystemInit();    
   
   /*
    * 设置“向量表偏移寄存器”。根据ARM文档，我们得到以下信息：
    *
    * 使用向量表偏移寄存器来确定：
    *  - 向量表是在RAM还是代码存储器中
    *  - 向量表的偏移量。
    */
   *((uint32_t*)0xE000ED08) = (uint32_t)&_stext;
   
   /*
    * 将“.data”段的初始化数据从flash复制到ram中的区域。
    */
   pSrc  = &_etext;
   pDest = &_sdata;
   while(pDest < &_edata)
   {
      *pDest++ = *pSrc++;
   }
   
   /*
    * 清除“.bss”段。
    */
   pDest = &_sbss;
   while(pDest < &_ebss)
   {
      *pDest++ = 0;
   }
   
   /*
    * 现在可以调用main函数了。
    * Scotty, energie...
    */       
   main();    
   
   /*
    * 如果“warp drive”有问题，停在这里。
    */
   while(1) {};    

} /* ResetHandler */

/*** EOF ***/
