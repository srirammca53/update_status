/*----------------------------------
  property.cpp
  $Date: 2001/08/18 07:08:04 $
  $Revision: 1.7 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include "dismscwarn.h"
#include "property.h"
#include "rwcommon.h"

void PROPERTY::store(
    const char *file
    ) {
    ofstream ofs(file);
    MAP::iterator i = m_prop.begin();
    while (i != m_prop.end()) {
        ofs << i->first << "=" << i->second << endl;
        i++;
    }
}

void PROPERTY::load(
    const char *file
    ) {
    ifstream ifs(file);
    if (!ifs) return;
    string line;
    while (getline(ifs, line)) {
#if 1
        istringstream istr(line);
        string key, val;
        if (getline(istr, key, '=') && getline(istr, val)) {
            m_prop[key] = val;
        }
#else
        string::size_type n = line.find_first_of('=');
        if (n != string::npos) {
            m_prop[line.substr(0, n)] = line.substr(n+1);
        }
#endif
    }
}

bool PROPERTY::get(
    const char* key,
    int & v
    ) {
    MAP::iterator i = m_prop.find(key);
    if (i != m_prop.end()) {
        v = atoi((i->second).c_str());
        return true;
    }
    return false;
}

bool PROPERTY::get(
    const char* key,
    unsigned int & v
    ) {
    MAP::iterator i = m_prop.find(key);
    if (i != m_prop.end()) {
        v = atoi((i->second).c_str());
        return true;
    }
    return false;
}

bool PROPERTY::get(
    const char* key,
    long & v
    ) {
    string s;
    if (get(key, s)) {
        v = atol(s.c_str());
        return true;
    }
    return false;
}

bool PROPERTY::get(
    const char* key,
    unsigned long & v
    ) {
    string s;
    if (get(key, s)) {
        v = strtoul(s.c_str(), NULL, 10);
        return true;
    }
    return false;
}

bool PROPERTY::get(
    const char* key,
    string & v
    ) {
    MAP::iterator i = m_prop.find(key);
    if (i != m_prop.end()) {
        v = i->second;
        return true;
    }
    return false;
}

void PROPERTY::set(
    const char *key,
    const int &i
    ) {
    char buf[64];
    sprintf(buf, "%d", i);
    set(key, buf);
}

void PROPERTY::set(
    const char *key,
    const unsigned int &i
    ) {
    char buf[64];
    sprintf(buf, "%d", i);
    set(key, buf);
}

void PROPERTY::set(
    const char *key,
    const long &l
    ) {
    char buf[64];
    sprintf(buf, "%ld", l);
    set(key, buf);
}

void PROPERTY::set(
    const char *key,
    const unsigned long &l
    ) {
    char buf[64];
    sprintf(buf, "%ld", l);
    set(key, buf);
}

void PROPERTY::set(
    const char *key,
    const char *val
    ) {
    string str_key = key;
    string str_val = val;
    m_prop[str_key] = str_val;
}
