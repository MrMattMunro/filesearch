/**
 * $RCSfile: UpdateFile.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.update;

import java.io.File;

import com.searchlocal.param.UpdateParam;
import com.searchlocal.thread.ThreadCheckThreadManager;
import com.searchlocal.thread.ThreadManager;

/**
 * 搜索文件存入文件容器
 * 
 * <p>Title: 搜索文件存入文件容器</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class UpdateFile {

	/** 文件容器 */
	private static UpdateFileContainer filecon = null;

	/**
	 * 搜索文件存入文件容器
	 * 
	 * @param param 搜索参数
	*/
	public void listen(UpdateParam param) {
		try {
			// 搜索对象路径
			String path = param.getPath();

			// 取得适合的并发数
			// int threadnum = FileUtil.getSubFileNums(path);
			// 新建文件容器
			filecon = new UpdateFileContainer();
			// 取得文件对象
			File file = new File(path);

			// 实行搜索文件路径
			UpdateFileTask updateFileTask = new UpdateFileTask();
			updateFileTask.init(file, param, filecon);
			ThreadManager.getThreadManager().executeThread(updateFileTask);
			
			// 实行搜索文件路径
			UpdateIndexTask updateIndex = new UpdateIndexTask();
			updateIndex.init(param, filecon);
			ThreadManager.getThreadManager().executeThread(updateIndex);

			// 检查是否退出搜索的线程
			CheckUpdateThreadPoolTask checktask = new CheckUpdateThreadPoolTask();
			checktask.init(filecon);
			ThreadCheckThreadManager.getThreadManager().executeThread(checktask);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
