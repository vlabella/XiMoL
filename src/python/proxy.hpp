/*****************************************************************************\
 *                                                                           *
 * library XiMoL                                                             *
 * Copyright (C) 2002, 2003, 2004 Florent Tournois                           *
 *                                                                           *
 * This library is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Lesser General Public                *
 * License as published by the Free Software Foundation; either              *
 * version 2.1 of the License, or (at your option) any later version.        *
 *                                                                           *
 * This library is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public          *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   *
 *                                                                           *
\*****************************************************************************/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** \file 
	\brief small proxy to wrap ximol stream.

    \author Tournois Florent
	\version 1.0

    $Id: proxy.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: proxy.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.1  2004/05/11 17:11:16  tournois
    wrapping xofstream in python. the begining


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_PYTHON_PROXY_HPP_
#define XIMOL_PYTHON_PROXY_HPP_

#include <map>

template < typename T >
class proxy
{
public:
    typedef proxy<T> this_t;
    typedef long index_t;
    typedef long counter_t;
    typedef std::map<index_t, T*> container_t;
    typedef std::map<index_t, counter_t> ref_counter_t;
    typedef typename container_t::iterator iterator;
    typedef typename container_t::const_iterator const_iterator;

public:
    ~proxy()
    { 
        iterator i(x.begin()), i_end(x.end());
        for(;i!=i_end;++i) 
            if (i->second!=NULL)
                delete i->second; 
    };

    static this_t & Singleton(){ static this_t s; return s; };

    T& operator[](index_t i)
    { 
        T* p=x[i];
        if (p==NULL) throw std::runtime_error("the object is not valide anymore");
        return *p; 
    };

    index_t set_new(T* p)
    { 
        if (p==NULL) return -1;
        index_t i(get_new_index());
        x[i]=p;
        count[i]=1;
        return i;
    };
    
    void add_ref(index_t i)
    {
        if (i==-1) return;
        count[i]+=1;
    };

    void del_ref(index_t i)
    {
        if (i==-1) return;
        count[i]-=1;
        if (count[i]==0)
        {
            delete x[i];
            x[i]=NULL;
        }
    };

    bool is_last_ref(index_t i)
    {
        if (i==-1) return false;
        return count[i]==1;
    };

    counter_t nb_ref(index_t i)
    {
        if (i==-1) return 0;
        return count[i];
    };

private:
    static index_t get_new_index(){static index_t i(0); return ++i; };    

private:
    container_t x;
    ref_counter_t count;
}; // end of class proxy

#endif // #ifndef XIMOL_PYTHON_PROXY_HPP_