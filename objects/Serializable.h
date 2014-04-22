//
//  Serializable.h
//  emptyExample
//
//  Created by Emmett Butler on 4/21/14.
//
//

#ifndef __emptyExample__Serializable__
#define __emptyExample__Serializable__

#include <iostream>
#include <map>

class Serializable {

};

template<typename T> Serializable * createT() { return new T; }
typedef std::map<std::string, Serializable*(*)()> map_type;
struct SerializableFactory {
    static map_type *creator_map;
    
    static Serializable * createInstance(std::string const& s) {
        map_type::iterator it = getMap()->find(s);
        if(it == getMap()->end())
            return 0;
        return it->second();
    }
    
protected:
    static map_type * getMap() {
        if(!creator_map) { creator_map = new map_type; }
        return creator_map;
    }
};

template<typename T>
struct SerializableRegister : SerializableFactory {
    SerializableRegister(std::string const& s) {
        getMap()->insert(std::make_pair(s, &createT<T>));
    }
};

#define REGISTER_DEC_TYPE(NAME) \
static SerializableRegister<NAME> reg

#define REGISTER_DEF_TYPE(NAME) \
SerializableRegister<NAME> NAME::reg(#NAME)

#endif /* defined(__emptyExample__Serializable__) */
