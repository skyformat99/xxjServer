#pragma once

//libgo��Linuxϵͳ��Ĭ��ʹ��ucontext��Э���������л���������ѡ�ʹ��boost.coroutine�����ucontext.
#define USE_BOOST_COROUTINE 1

#define USE_UCONTEXT 0

#define USE_FIBER 1

//libgo��Linuxϵͳ��Ĭ��ʹ��ucontext��Э���������л���������ѡ�ʹ��boost.context�����ucontext.
#define USE_BOOST_CONTEXT 1//������linux��������ѵı������

#define ENABLE_DEBUGGER 0

#define WITH_CARES 0

#ifdef WIN32
#define WITH_SAFE_SIGNAL 0
#else
#define  WITH_SAFE_SIGNAL 1
#endif

#define LIBGO_SINGLE_THREAD 0

