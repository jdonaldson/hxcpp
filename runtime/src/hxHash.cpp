#include <hxObject.h>
#include <gc_allocator.h>
#include <map>


class IntHash : public hxObject
{
#ifdef _WIN32
typedef int IntKey;
#else
typedef const int IntKey;
#endif

typedef std::map<IntKey,Dynamic, std::less<IntKey>, gc_allocator< std::pair<IntKey, Dynamic> > > Map;

private:
   Map mMap;
public:
   void set(int inKey,const Dynamic &inValue) { mMap[inKey] = inValue; }
   Dynamic get(int inKey)
   {
      Map::iterator i = mMap.find(inKey);
      if (i==mMap.end()) return null();
      return i->second;
   }
   bool exists(int inKey) { return mMap.find(inKey)!=mMap.end(); }
   bool remove(int inKey)
   {
      Map::iterator i = mMap.find(inKey);
      if (i==mMap.end()) return false;
      mMap.erase(i);
      return true;
   }
   Dynamic keys()
   {
      Array<Int> result(0,mMap.size());
      for(Map::iterator i=mMap.begin();i!=mMap.end();++i)
         result.Add(i->first);
      return result;
   }
   Dynamic values()
   {
      Array<Dynamic> result(0,mMap.size());
      for(Map::iterator i=mMap.begin();i!=mMap.end();++i)
         result.Add(i->second);
      return result;
   }
   String toString()
   {
      String result = L"{ ";
      Map::iterator i=mMap.begin();
      while(i!=mMap.end())
      {
         result += String(i->first) + String(L" => ",1) + i->second;
         ++i;
         if (i!=mMap.end())
            result+= L",";
      }

      return result + L"}";
   }

};



hxObject SHARED * CreateIntHash() { return new IntHash; }
void __int_hash_set(Dynamic &inHash,int inKey,const Dynamic &value)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   h->set(inKey,value);
}

Dynamic  __int_hash_get(Dynamic &inHash,int inKey)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   return h->get(inKey);
}

bool  __int_hash_exists(Dynamic &inHash,int inKey)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   return h->exists(inKey);
}

bool  __int_hash_remove(Dynamic &inHash,int inKey)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   return h->remove(inKey);
}

Dynamic __int_hash_keys(Dynamic &inHash)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   return h->keys();
}

Dynamic __int_hash_values(Dynamic &inHash)
{
   IntHash *h = dynamic_cast<IntHash *>(inHash.GetPtr());
   return h->values();
}
