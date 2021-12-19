/**************************************************/ 
/**********************MsgBinaryArchive.h****************************/ 
    
#include <strstream>
#include "boost/serialization/string.hpp"
#include "boost/serialization/list.hpp"
#include "msg_binary_iarchive.h"
#include "msg_binary_oarchive.h"
    
#define MSG1(mn,t1,n1)/
struct mn/
{/
  t1 vn1;/
    template<class Archive> void serialize(Archive & ar, const unsigned int version)/
      {/
	ar & vn1;/
	  }/
      };
    
#define MSG2(mn,t1,n1,t2,n2)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      template<class Archive> void serialize(Archive & ar, const unsigned int version)/
	{/
	  ar & n1;/
	    ar & n2;/
	      }/
    	};
    
#define MSG3(mn,t1,n1,t2,n2,t3,n3)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	template<class Archive> void serialize(Archive & ar, const unsigned int version)/
	  {/
	    ar & n1;/
	      ar & n2;/
		ar & n3;/
		  }/
	  };
    
#define MSG4(mn,t1,n1,t2,n2,t3,n3,t4,n4)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  template<class Archive> void serialize(Archive & ar, const unsigned int version)/
	    {/
	      ar & n1;/
		ar & n2;/
		  ar & n3;/
		    ar & n4;/
		      }/
	    };
    
#define MSG5(mn,t1,n1,t2,n2,t3,n3,t4,n4,t5,n5)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  t5 n5;/
	    template<class Archive> void serialize(Archive & ar, const unsigned int version)/
	      {/
		ar & n1;/
		  ar & n2;/
		    ar & n3;/
		      ar & n4;/
    			ar & n5;/
			  }/
	      };
    
#define MSG6(mn,t1,n1,t2,n2,t3,n3,t4,n4,t5,n5,t6,n6)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  t5 n5;/
	    t6 n6;/
	      template<class Archive> void serialize(Archive & ar, const unsigned int version)/
    		{/
		  ar & n1;/
		    ar & n2;/
		      ar & n3;/
    			ar & n4;/
			  ar & n5;/
			    ar & n6;/
			      }/
		};
    
#define MSG7(mn,t1,n1,t2,n2,t3,n3,t4,n4,t5,n5,t6,n6,t7,n7)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  t5 n5;/
	    t6 n6;/
	      t7 n7;/
    		template<class Archive> void serialize(Archive & ar, const unsigned int version)/
		  {/
		    ar & n1;/
		      ar & n2;/
    			ar & n3;/
			  ar & n4;/
			    ar & n5;/
			      ar & n6;/
				ar & n7;/
				  }/
		  };
    
#define MSG8(mn,t1,n1,t2,n2,t3,n3,t4,n4,t5,n5,t6,n6,t7,n7,t8,n8)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  t5 n5;/
	    t6 n6;/
	      t7 n7;/
    		t8 n8;/
		  template<class Archive> void serialize(Archive & ar, const unsigned int version)/
		    {/
		      ar & n1;/
    			ar & n2;/
			  ar & n3;/
			    ar & n4;/
			      ar & n5;/
				ar & n6;/
				  ar & n7;/
				    ar & n8;/
				      }/
		    };
    
#define MSG9(mn,t1,n1,t2,n2,t3,n3,t4,n4,t5,n5,t6,n6,t7,n7,t8,n8,t9,n9)/
struct mn/
{/
  t1 n1;/
    t2 n2;/
      t3 n3;/
	t4 n4;/
	  t5 n5;/
	    t6 n6;/
	      t7 n7;/
    		t8 n8;/
		  t9 n9;/
		    template<class Archive> void serialize(Archive & ar, const unsigned int version)/
		      {/
    			ar & n1;/
			  ar & n2;/
			    ar & n3;/
			      ar & n4;/
				ar & n5;/
				  ar & n6;/
				    ar & n7;/
				      ar & n8;/
					ar & n9;/
					  }/
		      };
    
class MsgPack
{
 public:
 MsgPack():
  _oa(_os, boost::archive::no_header)
    {}
    
  template <class T>
    MsgPack& operator & (const T & v)
    {
      reset();
      _oa & v;
    
      return *this;
    }
    
  template <class T>
    MsgPack& operator << (const T & v)
    {
      _oa & v;
    
      return *this;
    }
    
  void reset()
  {
    _os.freeze(false);
    _os.seekp(0);
    _os.seekg(0);
  }
    
  const char* buffer()
  {
    return _os.str();
  }
    
  size_t size()
  {
    return _os.pcount();
  }
    
 private:
  std::strstream							_os;
  boost::archive::msg_binary_oarchive 	_oa;
};
    
class MsgUnpack
{
 public:
 MsgUnpack():
  _ia(_is, boost::archive::no_header)
    {}
    
  void reset(const char* buf, size_t size)
  {
    if (_is.pcount())
      {
	_is.seekp(0);
	_is.seekg(0);
      }
    _is.write(buf, (std::streamsize)size);
  }
    
  template <class T>
    MsgUnpack& operator >> (T & v)
    {
      _ia & v;
    
      return *this;
    }
    
 private:
  std::strstream							_is;
  boost::archive::msg_binary_iarchive 	_ia;
};
