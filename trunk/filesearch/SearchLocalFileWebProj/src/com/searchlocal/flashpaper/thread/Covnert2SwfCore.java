/**
 * $RCSfile: Covnert2SwfCore.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.flashpaper.thread;

import java.io.File;

/**
 * 将文档转换成SWF
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class Covnert2SwfCore {

	public static void listen(File inFileObj, File outFilePath) {
		// 开始监控是否同步
		Covnert2SwfTask checkSearcherTask = new Covnert2SwfTask(inFileObj, outFilePath);
		Covnert2SwfThreadManager.getThreadManager().executeThread(checkSearcherTask);
	}
}
