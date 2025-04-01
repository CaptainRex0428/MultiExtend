#pragma once

#ifdef _DEBUG
#define MULTIEXTEND_TIMER() long double varn##__LINE__ = 0; MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,false,varn##__LINE__);
#define MULTIEXTEND_TIMER_TRACE() long double varn##__LINE__ = 0; MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,true,varn##__LINE__);
#define MULTIEXTEND_TIMER_TRACE_TAG(traceName) long double varn##__LINE__ = 0; MultiExtend::Timer timer##__LINE__(__FUNCTION__,#traceName,true,varn##__LINE__);
#define MULTIEXTEND_TIMER_RETURN(varn) MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,false,varn);
#define MULTIEXTEND_TIMER_TRACE_RETURN(varn) MultiExtend::Timer timer##__LINE__(__FUNCTION__,__FUNCSIG__,true,varn);
#define MULTIEXTEND_TIMER_TRACE_TAG_RETURN(traceName,varn) MultiExtend::Timer timer##__LINE__(__FUNCTION__,#traceName,true,varn);
#else
#define MULTIEXTEND_TIMER()
#define MULTIEXTEND_TIMER_TRACE()
#define MULTIEXTEND_TIMER_TRACE_TAG(traceName)
#define MULTIEXTEND_TIMER_RETURN(varn)
#define MULTIEXTEND_TIMER_TRACE_RETURN(varn)
#define MULTIEXTEND_TIMER_TRACE_TAG_RETURN(traceName,varn)
#endif