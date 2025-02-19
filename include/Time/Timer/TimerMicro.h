#pragma once

#define MULTIEXTEND_TIMER_TRACE_NSTORE() double varn##__LINE__ = 0; MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,true,varn##__LINE__)
#define MULTIEXTEND_TIMER_TRACE_STORE(varn) MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,true,varn)

#define MULTIEXTEND_TIMER_NTRACE_NSTORE() double varn##__LINE__ = 0; MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,false,varn##__LINE__)
#define MULTIEXTEND_TIMER_NTRACE_STORE(varn) MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,false,varn)