/**************************************************/ 
/**********msg_binary_oarchive.h****************************************/ 
    
// 这文件内容是直接复制的boost的binary_oarchive.hpp的内容做了点儿修改
    
#include <ostream>
    
#include <boost/archive/binary_oarchive_impl.hpp>
#include <boost/archive/impl/basic_binary_oprimitive.ipp>
#include <boost/archive/impl/basic_binary_oarchive.ipp>

namespace boost { 
  namespace archive {
    
    class msg_binary_oarchive : 
      public binary_oarchive_impl<
      msg_binary_oarchive, std::ostream::char_type, std::ostream::traits_type
      >
      {
      public:
    	typedef binary_oarchive_impl<
	  msg_binary_oarchive, std::ostream::char_type, std::ostream::traits_type
	  > base;
      msg_binary_oarchive(std::ostream & os, unsigned int flags = 0) :
    	binary_oarchive_impl<
	  msg_binary_oarchive, std::ostream::char_type, std::ostream::traits_type
	  >(os, flags)
	  {}
      msg_binary_oarchive(std::streambuf & bsb, unsigned int flags = 0) :
    	binary_oarchive_impl<
	  msg_binary_oarchive, std::ostream::char_type, std::ostream::traits_type
	  >(bsb, flags)
	  {}
    
    	template<class T>
	  void save_override(T & t, BOOST_PFTO int)
	  {
	    BOOST_MPL_ASSERT_NOT(( boost::is_pointer<T> ));
	    base::save_override(t, 0);
	  }
    
    	// 这些信息都不要了
    	void save_override(const boost::archive::class_id_optional_type &, int){}
    	void save_override(const boost::archive::tracking_type &, int){}
    	void save_override(const boost::archive::version_type &, int){}
    
      };
    
    typedef msg_binary_oarchive naked_binary_oarchive;
    
  } // namespace archive
} // namespace boost
    
// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::msg_binary_oarchive)
  BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::msg_binary_oarchive)
