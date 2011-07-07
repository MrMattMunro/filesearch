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
package com.searchlocal.thread.customdic;

/**
 * 监控字典文件,有更新则更新自定义字典,并重建索引文件
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckCustomDicCore {

	public static void listen() {
		// 开始监控是否开始检索
		CreateCustomDicTask checkSearcherTask = new CreateCustomDicTask();
		CheckCustomDicThreadManager.getThreadManager().executeThread(checkSearcherTask);
	}
}
