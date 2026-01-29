#ifndef GDGDK_MACROS_H
#define GDGDK_MACROS_H

#define GDKOBJECT(m_wrapper_class, m_native_class)\
private:\
    m_native_class _native_object = nullptr;\
\
public:\
    static Ref<m_wrapper_class> create(m_native_class obj);    

#endif // GDGDK_MACROS_H