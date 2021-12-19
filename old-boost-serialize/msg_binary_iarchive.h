/**************************************************/ 
/***************msg_binary_iarchive.h ***********************************/ 
    
// 这文件内容是直接复制的boost的binary_iarchive.hpp的内容做了点儿修改
    
#include <istream>
    
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>
#include <boost/archive/impl/basic_binary_iarchive.ipp>
    
namespace boost { 
  namespace archive {
    
    class naked_binary_iarchive : 
      public binary_iarchive_impl<
      boost::archive::naked_binary_iarchive, 
      std::istream::char_type, 
      std::istream::traits_type
      >
      {
      public:
      naked_binary_iarchive(std::istream & is, unsigned int flags = 0) :
    	binary_iarchive_impl<
	  naked_binary_iarchive, std::istream::char_type, std::istream::traits_type
	  >(is, flags)
	  {}
      naked_binary_iarchive(std::streambuf & bsb, unsigned int flags = 0) :
    	binary_iarchive_impl<
	  naked_binary_iarchive, std::istream::char_type, std::istream::traits_type
	  >(bsb, flags)
	  {}
      };
    
  } // namespace archive
} // namespace boost
    
namespace boost { 
  namespace archive {
    
    class msg_binary_iarchive : 
      public binary_iarchive_impl<
      boost::archive::msg_binary_iarchive, 
      std::istream::char_type, 
      std::istream::traits_type
      >{
    
      public detail::shared_ptr_helper
      {
      public:
    	typedef binary_iarchive_impl<
	  boost::archive::msg_binary_iarchive, 
	  std::istream::char_type, 
	  std::istream::traits_type
	  > base;
      msg_binary_iarchive(std::istream & is, unsigned int flags = 0) :
    	binary_iarchive_impl<
	  msg_binary_iarchive, std::istream::char_type, std::istream::traits_type
	  >(is, flags)
	  {}
      msg_binary_iarchive(std::streambuf & bsb, unsigned int flags = 0) :
    	binary_iarchive_impl<
	  msg_binary_iarchive, std::istream::char_type, std::istream::traits_type
	  >(bsb, flags)
	  {}
    
    	template<class T>
	  void load_override(T & t, BOOST_PFTO int)
	  {
	    BOOST_MPL_ASSERT_NOT(( boost::is_pointer<T> ));
	    base::load_override(t, 0);
	  }
    
    	// 这些信息都不要了
    	void load_override(boost::archive::class_id_optional_type &, int){}
    	void load_override(boost::archive::tracking_type & t, int){t.t = false;}
    	void load_override(boost::archive::version_type & t, int){t.t = 0;}
      };
    
  } // namespace archive
} // namespace boost
    
// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::msg_binary_iarchive)
  BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::msg_binary_iarchive)
