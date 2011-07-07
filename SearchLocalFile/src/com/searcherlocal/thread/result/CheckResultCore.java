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
package com.searcherlocal.thread.result;

/**
 * 当检查有需要检索对象时,生成结果集存入数据库
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckResultCore {

	public static void listen() {
		// 开始监控是否开始检索
		CreateResultTask checkSearcherTask = new CreateResultTask();
		CheckResultThreadManager.getThreadManager().executeThread(checkSearcherTask);
	}
}
