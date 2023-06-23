/* 
 * CairoPointer.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Vis::CairoPointer.
 */

#ifndef CDPL_VIS_CAIROPOINTER_HPP
#define CDPL_VIS_CAIROPOINTER_HPP

#include "CDPL/Vis/APIPrefix.hpp"


typedef struct _cairo cairo_t;
typedef struct _cairo_surface cairo_surface_t;
typedef struct _cairo_pattern cairo_pattern_t;


namespace CDPL 
{

    namespace Vis
    {
        
        template <typename T> struct CairoPointerTraits;

        /**
         * \brief Specialization of \c %CairoPointerTraits for the object type \c cairo_t.
         * \see Vis::CairoPointer
         */
        template <>
        struct CDPL_VIS_API CairoPointerTraits<cairo_t>
        {

            /**
             * \brief Increments the reference count of the object pointed to by \a p by \e 1.
             * \return The argument \a p.
             */
            static cairo_t* reference(cairo_t* p) throw();

            /**
             * \brief Decrements the reference count of the object pointed to by \a p by \e 1.
             */
            static void destroy(cairo_t* p) throw();
        };
    
        /**
         * \brief Specialization of \c %CairoPointerTraits for the object type \c cairo_surface_t.
         * \see Vis::CairoPointer
         */
        template <>
        struct CDPL_VIS_API CairoPointerTraits<cairo_surface_t>
        {
    
            /**
             * \brief Increments the reference count of the object pointed to by \a p by \e 1.
             * \return The argument \a p.
             */
            static cairo_surface_t* reference(cairo_surface_t* p) throw();
        
            /**
             * \brief Decrements the reference count of the object pointed to by \a p by \e 1.
             */
            static void destroy(cairo_surface_t* p) throw();
        };

        /**
         * \brief Specialization of \c %CairoPointerTraits for the object type \c cairo_pattern_t.
         * \see Vis::CairoPointer
         */
        template <>
        struct CDPL_VIS_API CairoPointerTraits<cairo_pattern_t>
        {
    
            /**
             * \brief Increments the reference count of the object pointed to by \a p by \e 1.
             * \return The argument \a p.
             */
            static cairo_pattern_t* reference(cairo_pattern_t* p) throw();
    
            /**
             * \brief Decrements the reference count of the object pointed to by \a p by \e 1.
             */            
            static void destroy(cairo_pattern_t* p) throw();
        };

        /**
         * \brief A smart pointer managing the lifetime of allocated \e Cairo data structures.
         *
         * Data structures required for interfacing with the <em>Cairo 2D Graphics Library</em> [\ref CAIRO] 
         * generally have to be allocated dynamically via specialized functions and are passed as pointers
         * from and to the \e Cairo library. The lifetime of an allocated data structure is determined by its
         * reference count which has to be managed explicitely by the client code. \c %CairoPointer automatizes
         * the reference count management by incrementing the reference count of the wrapped object whenever a
         * \c %CairoPointer instance is copied, and decrementing the reference count if the \c %CairoPointer is
         * destroyed or gets overwritten by assignment of another pointer instance of the same type. 
         *
         * Since the \e Cairo library is written in C and functions for changing the reference count of different
         * \e Cairo data structures are named differently, \c %CairoPointer relies on the traits class \c CairoPointerTraits<T>
         * which has to be specialized for a particular data type and performs the actual work of incrementing
         * and decrementing the reference count by calling the appropriate functions. Note that only a \e Cairo data structure
         * for which such a specialization exists can be managed by a \c %CairoPointer. An attempt to instantiate \c %CairoPointer
         * with an unsupported type will result in a compile time error.
         *
         * Currently specializations for the following types are provided:
         *   - \c cairo_t
         *   - \c cairo_surface_t
         *   - \c cairo_pattern_t
         *
         * \tparam T The type of the managed \e Cairo data structure.
         */
        template <typename T>
        class CairoPointer
        {
      
        public:
            /**
             * \brief Constructs a \c %CairoPointer that manages the reference count of the object
             *        pointed to by \a ptr.
             * \param ptr A pointer to the object whose reference count has to be managed.
             * \note The reference count of the object pointed to by \a ptr is not incremented.
             */
            explicit CairoPointer(T* ptr = 0) throw();

            /**
             * \brief Constructs a copy of the \c %CairoPointer \a ptr.
             * \param ptr The other \c %CairoPointer to copy.
             * \post The reference count of the object pointed to by \a ptr is incremented by \e 1.
             */
            CairoPointer(const CairoPointer& ptr) throw();

            /**
             * \brief Destroys the \c %CairoPointer.
             * \post The reference count of the pointed-to object is decremented by \e 1.
             */
            ~CairoPointer();

            /**
             * \brief Assignment operator.
             *
             * The pointer to the currently referenced object will be replaced by a pointer to the object referenced
             * by \a ptr. The reference count of the currently pointed-to object will be decremented and the reference
             * count of the object pointed to by \a ptr is incremented. A self assignment has no effect.
             *
             * \param ptr The other \c %CairoPointer to copy.
             * \return A reference to itself.
             * \post The \c %CairoPointer references the same object as \a ptr. The reference count of the
             *       new pointed-to object is incremented by \e 1 and the reference count of the old 
             *       pointed-to object is decremented by \e 1.
             */
            CairoPointer& operator=(const CairoPointer& ptr) throw();

            /**
             * \brief Tells whether this \c %CairoPointer references an object or holds a \e null pointer.
             * \return \c false if an object is referenced, and \c true otherwise.
             */
            bool operator!() const throw();

            /**
             * \brief Returns a non-\c const reference to the pointed-to object.
             * \return A non-\c const reference to the pointed-to object.
             * \note A \e null pointer check is not performed.
             */
            T& operator*() const throw();

            /**
             * \brief Returns a pointer to the referenced object.
             *
             * The method is equivalent to get().
             *
             * \return A pointer to the referenced object, or \e null if no object is referenced.
             * \see get()
             */
            T* operator->() const throw();
 
            /**
             * \brief Returns a pointer to the referenced object.
             * \return A pointer to the referenced object, or \e null if no object is referenced.
             */
            T* get() const throw();

            /**
             * \brief Releases the currently referenced object.
             * \return A pointer to the formerly referenced object, or \e null if no object was referenced.
             * \post The reference count of the previously pointed-to object is decremented by \e 1
             *       and the internal pointer to the referenced object is set to \e null.
             */
            T* release() throw();

            /**
             * \brief Replaces the current object reference with a reference to the object pointed to by \a ptr.
             *
             * The method has no effect if the currently referenced object and the object pointed to by
             * \a ptr are identical.
             *
             * \post The reference count of the previously pointed-to object is decremented by \e 1. The
             *       newly referenced object is the object pointed to by \a ptr.
             */
            void reset(T* ptr = 0) throw();

        private:
            T* pointer;
        };
    }
}


// Implementation

template <typename T>
CDPL::Vis::CairoPointer<T>::CairoPointer(T* p) throw() : pointer(p) {}

template <typename T>
CDPL::Vis::CairoPointer<T>::CairoPointer(const CairoPointer& other) throw() 
    : pointer(CairoPointerTraits<T>::reference(other.pointer)) {}

template <typename T>
CDPL::Vis::CairoPointer<T>::~CairoPointer() 
{ 
    CairoPointerTraits<T>::destroy(pointer); 
}

template <typename T>
CDPL::Vis::CairoPointer<T>& CDPL::Vis::CairoPointer<T>::operator=(const CairoPointer& other) throw() 
{
    if (this != &other) {
        CairoPointerTraits<T>::destroy(pointer);
        pointer = CairoPointerTraits<T>::reference(other.pointer);
    }

    return *this;
}

template <typename T>
bool CDPL::Vis::CairoPointer<T>::operator!() const throw() 
{
    return !pointer;
}

template <typename T>
T& CDPL::Vis::CairoPointer<T>::operator*() const throw() 
{ 
    return *pointer; 
}

template <typename T>
T* CDPL::Vis::CairoPointer<T>::operator->() const throw()
{ 
    return pointer; 
}

template <typename T>
T* CDPL::Vis::CairoPointer<T>::get() const throw()
{ 
    return pointer; 
}

template <typename T>
T* CDPL::Vis::CairoPointer<T>::release() throw()
{
    T* tmp = pointer;
    pointer = 0;
    return tmp;
}

template <typename T>
void CDPL::Vis::CairoPointer<T>::reset(T* p) throw()
{
    if (p != pointer) {
        CairoPointerTraits<T>::destroy(pointer);
        pointer = p;
    }
}

#endif // CDPL_VIS_CAIROPOINTER_HPP
