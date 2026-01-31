#ifndef GDGDK_MACROS_H
#define GDGDK_MACROS_H  

#define GETTER(m_var, type)\
    type get##m_var() const;

#define SETTER(m_var, type)\
    void set##m_var(type p_value);

#define GETTER_SETTER(m_var, type)\
    GETTER(m_var, type)\
    SETTER(m_var, type)
    
#endif // GDGDK_MACROS_H