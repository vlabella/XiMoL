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

/** \page cvs CVS access

\section anonymous Anonymous CVS Access 

This project's SourceForge.net CVS repository can be checked out through anonymous (pserver) CVS with the following instruction set. 
The module you wish to check out must be specified as the modulename.  The modulename is 'ximol'.
When prompted for a password for anonymous, simply press the Enter key. 

<pre>
cvs -d:pserver:anonymous@cvs.ximol.sourceforge.net:/cvsroot/ximol login 
cvs -z3 -d:pserver:anonymous@cvs.ximol.sourceforge.net:/cvsroot/ximol co ximol 
</pre>

Updates from within the module's directory do not need the -d parameter.

\section developper Developer CVS Access via SSH 

Only project developers can access the CVS tree via this method. SSH1 must be installed on your client machine. 
Substitute modulename and developername with the proper values. Enter your site password when prompted. 

<pre>
export CVS_RSH=ssh 
cvs -z3 -d:ext:developername@cvs.ximol.sourceforge.net:/cvsroot/ximol co ximol 
</pre>

*/