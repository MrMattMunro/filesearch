/*
 * Copyright (c) 1999-2004 Sourceforge JCOM Project.
 * All rights reserved. Originator: Dan Adler (http://danadler.com).
 * Get more information about JCOM at http://sourceforge.net/projects/JCOM-project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
package com.web.searchlocal.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

/**
 * Utility class to centralize the way in which the JCOM JNI library is loaded.
 * 
 * <p>
 * If system property {@link #JCOM_DLL_PATH} is defined, the file located there
 * will be loaded as the JCOM dll. If the system property is not defined,
 * normal library paths will be used to load the JCOM dll. This means it
 * defaults to the previous behavior for existing applications.
 * <p>
 * The standard behavior for most applications is that LoadLibrary() will be
 * called to load the dll. LoadLibary searches directories specified in the
 * variable java.library.path . This is why most test cases specify
 * -Djava.library.path in their command line arguments
 * <p>
 * Submitted sourceforge ticket 1493647
 * 
 * @author Scott Dickerson (sjd78)
 */
public final class LibraryLoader {
	/**
	 * Name of system property (currently <tt>JCOM.dll.path</tt>) that may
	 * contain an absolute path to the JNI library.
	 */
	public static final String JCOM_DLL_PATH = "jcom.dll.path";

	/**
	 * Load the JCOM dll either from an absolute path defined in system
	 * property {@link #JCOM_DLL_PATH} or as a general library called "<tt>JCOM</tt>".
	 * 
	 * @throws UnsatisfiedLinkError
	 *             if the library does not exist.
	 */
	public static void loadJCOMLibrary() {
		String path = System.getProperty(JCOM_DLL_PATH);
		if (path != null) {
			System.load(path);
		} else {
			try {
				InputStream inputStream = Thread.currentThread().getContextClassLoader().getResource("/jcomtemp.dll").openStream();
				File temporaryDll = File.createTempFile("jcom", ".dll");
				FileOutputStream outputStream = new FileOutputStream(temporaryDll);
				byte[] array = new byte[8192];
				for (int i = inputStream.read(array); i != -1; i = inputStream
						.read(array)) {
					outputStream.write(array, 0, i);
				}
				outputStream.close();
				System.setProperty(JCOM_DLL_PATH, temporaryDll.getPath());
				// System.load(JCOM_DLL_PATH);
				System.load(temporaryDll.getPath());
				System.out.println(System.getProperty("java.library.path"));
//				System.loadLibrary(libname)
			    //temporaryDll.deleteOnExit();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

} // LibraryLoader
