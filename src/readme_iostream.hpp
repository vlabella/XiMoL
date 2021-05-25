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

/** \page ios Why iostream is good for you ?

Here is the introduction of the article "An Iostream-Compatible Socket Wrapper" 
from the C/C++ User Journal (December 2001) written by Maciej Sobczak. 
This article is really great and you should read it entirely.

\section article Introduction of the article "An Iostream-Compatible Socket Wrapper" (CUJ Dec 2001)

When I was attending the C++ course at my university (which followed the C course), I was told that now there are better tools to do the job than before, and that, for example, the following form should no longer be used:

\code
fprintf(stdout, "Hello World!");
\endcode

Instead, the object-based approach is preferred:

\code
cout << "Hello World!" << endl;
\endcode

I know a lot of people who would argue that the second line is not a bit more object-oriented than the first; the former is even better, because it clearly states what operation is performed on what entity. What is the improvement, then? The improvement comes from code reuse and the polymorphism that the iostream-compatible objects expose. Consider this:

\code
void printHello(ostream &stream)
{
    stream << "Hello World!" << endl;
}
\endcode

printHello is reusable, because it treats its arguments polymorphically [1]. You can use it with the standard cout object, or with any other stream you can invent, whether it is connected to a file (by std::ofstream) or to a string buffer (by std::ostringstream) or to something else derived from ostream. Indeed, with a slight change you can make it work with all of the standard streams, including the wide-character versions. Beyond that, it will also work with anything else that supports operator<< and understands endl, whether the stream happens to be derived from a standard stream class or not:

\code
template<typename T>
void printHello(T &stream)
{
    stream << "Hello World!" << endl;
}
\endcode

The possibilities are countless, and there is tons of code like the above to reuse. 
There is one minor problem, though. The standard library cannot provide all the classes needed for all I/O, because I/O programming is not limited to terminals, files, and memory devices like strings. 
Computers are used also for network communication where sockets are the popular abstraction. 
Is there any possibility to use the existing, iostream-compatible code in programs based on socket networking? Of course, there is.

*/