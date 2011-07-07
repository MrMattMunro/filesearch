/**
 * $RCSfile: CheckSearcherCore.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.searcher;

/**
 * 程序启动时启动搜索对象线程
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckSearcherCore {

	public static void listen() {
		// 开始监控是否同步
		CheckSearcherTask checkSearcherTask = new CheckSearcherTask();
		CheckSearcherThreadManager.getThreadManager().executeThread(checkSearcherTask);
	}
}
