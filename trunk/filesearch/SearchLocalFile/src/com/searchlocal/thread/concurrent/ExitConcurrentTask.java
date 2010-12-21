package com.searchlocal.thread.concurrent;

import java.util.Enumeration;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ThreadPoolExecutor;

import com.searchlocal.bean.CurrentFileBean;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;

/**
 * 监听是否需要停止同步线程
 * 
 * <p>Title: 监听是否需要停止同步线程</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ExitConcurrentTask extends CRunnable {

	/** 文件容器 */
	private List<ConcurrentFileContainer> fileconlist;
	
	/**
	 * 初期化操作
	 * 
	 * @param filecon 文件容器
	 */
	public void init(List fileconlist) {
		this.fileconlist = fileconlist;
	}

	public void setTimeOut() {
	}

	/**
	 * 线程执行
	 */
	public void run() {
		while (true) {
			synchronized (this) {
				ThreadUtil.sleep(120000);
				System.out.println("开始检查是否需要退出");
				// 取得文件容器中的DB文件
				boolean allhascurrent = true;
				for(int i=0;i<fileconlist.size();i++){
					ConcurrentFileContainer filecon = fileconlist.get(i);
					ConcurrentHashMap<String, CurrentFileBean> currentFiles = filecon.getDbfiles();
					Enumeration<CurrentFileBean> beans = currentFiles.elements();
					while (beans.hasMoreElements()) {
						CurrentFileBean bean = beans.nextElement();
						if(!bean.isHascurrent()){
							allhascurrent = false;
							break;
						}
					}
				}

				
				System.out.print("allhascurrent: " + allhascurrent);
				// 停止同步
				if(allhascurrent){
					ThreadPoolExecutor exector = ConcurrentFileThreadManager.getThreadManager().getPool();
					exector.shutdown();
					exector = BaseConcurrentThreadManager.getThreadManager().getPool();
					exector.shutdown();
                    // 重起搜索
					SearchlocalApp.completeWork();
					String slfilepath = ConstantExeFileUtil.getOpenerbyId("slfile");
					CourseUtil.restart(slfilepath);
					break;
				}
			}
		}
	}
}
