package com.searchlocal.thread.concurrent;

import com.searchlocal.constants.Constant;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;

/**
 * 是否开始同步监控线程
 * 
 * <p>Title: 同步文件任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentTimerTask extends CRunnable {

	public void run() {
		while (true) {
			ThreadUtil.sleep(300000);
			if (ThreadUtil.isMidDay()) {
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_UPDATINGINDEX);
				System.out.println("start listen file");
				ConcurrentFile.listen();
				break;
			}
		}
	}
}
