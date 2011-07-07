/* 
 * Copyright (C) 2001-2005 Jacek Sieka, arnetheduck on gmail point com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#if !defined(AFX_SEMAPHORE_H__99141DD0_FECE_4131_BC9B_7BE4CF216874__INCLUDED_)
#define AFX_SEMAPHORE_H__99141DD0_FECE_4131_BC9B_7BE4CF216874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 

class Semaphore  
{
 
public:
	Semaphore() throw() {
		h = CreateSemaphore(NULL, 0, MAXLONG, NULL);
	};

	void signal() throw() {
		ReleaseSemaphore(h, 1, NULL);
	}

	bool wait() throw() { return WaitForSingleObject(h, INFINITE) == WAIT_OBJECT_0; };
	bool wait(DWORD millis) throw() { return WaitForSingleObject(h, millis) == WAIT_OBJECT_0; };

	~Semaphore() throw() {
		CloseHandle(h);
	};

private:
	HANDLE h; 
	Semaphore(const Semaphore&);
	Semaphore& operator=(const Semaphore&);

};

#endif // !defined(AFX_SEMAPHORE_H__99141DD0_FECE_4131_BC9B_7BE4CF216874__INCLUDED_)

/**
 * @file
 * $Id: Semaphore.h,v 1.1.1.1 2005/01/05 12:30:24 liny Exp $
 */
