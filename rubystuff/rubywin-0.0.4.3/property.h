/*----------------------------------
  property.h
  $Date: 2001/08/18 07:08:04 $
  $Revision: 1.4 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <map>
using namespace std;
typedef map<string, string> MAP;

class PROPERTY {
public:
    PROPERTY(){}
    ~PROPERTY(){}
    void load(const char *file);
    void store(const char *file);
    bool get(const char* key, int &i);
    bool get(const char* key, unsigned int &i);
    bool get(const char* key, long &l);
    bool get(const char* key, unsigned long &l);
    bool get(const char* key, string &s);
    bool get(const string &key, string &s) {
        return get(key.c_str(), s);
    }

    void set(const char *key, const int &i);
    void set(const char *key, const unsigned int &i);
    void set(const char *key, const long &l);
    void set(const char *key, const unsigned long &l);

    void set(const char *key, const char *val);
    void set(const string &key, const char *val) {
        set(key.c_str(), val);
    }
private:
    MAP m_prop;
};

#endif
