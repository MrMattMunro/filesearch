
/**
 * $RCSfile: CheckUpdateThreadPoolTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.update;

import java.util.concurrent.ThreadPoolExecutor;

import com.searchlocal.thread.ThreadManager;
import com.searchlocal.thread.base.CRunnable;

/**
 * 检查是否退出
 * 
 * <p>Title: 检查是否退出</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckUpdateThreadPoolTask extends CRunnable {

	/** 文件容器 */
	private UpdateFileContainer filecon;

	/** 是否完成标志位 */
	private static boolean isdone = false;

	/** 
	 * 初始化
	 * 
	 * @param filecon 文件容器
	 */
	public void init(UpdateFileContainer filecon) {
		this.filecon = filecon;
	}

	public void run() {
		while (true) {
			try {
				Thread.sleep(10000);
				if (this.filecon.isIsdone() || isdone) {
					continue;
				}
				ThreadPoolExecutor pool = ThreadManager.getThreadManager().getPool();

				synchronized (this) {
					int addFileNum = filecon.getAddfileNum();
					int delFileNum = filecon.getDelfileNum();
					System.out.println("filecon.getAddfileNum():" + addFileNum);
					System.out.println("filecon.getDelfileNum():" + delFileNum);
					int activecount = pool.getActiveCount();
					if (addFileNum == 0 && delFileNum ==0 && activecount == 1) {
						// 清空資源
						filecon.clearAll();
						this.filecon.setIsdone(true);
						isdone = true;
						break;
					}
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * @return the isdone
	 */
	public static boolean isIsdone() {
		return isdone;
	}
}
