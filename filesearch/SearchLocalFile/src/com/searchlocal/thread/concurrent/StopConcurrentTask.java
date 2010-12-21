package com.searchlocal.thread.concurrent;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ThreadPoolExecutor;

import com.searchlocal.bean.CurrentFileBean;
import com.searchlocal.lucene.IndexMaker;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;

/**
 * 监听是否需要停止同步线程
 * 
 * <p>Title: 监听是否需要停止同步线程</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class StopConcurrentTask extends CRunnable {

	/** 文件容器 */
	private ConcurrentFileContainer filecon;
	
	/** 单个搜索对象 */
	private CreateNewParam param;


	/**
	 * 初期化操作
	 * 
	 * @param filecon 文件容器
	 */
	public void init(ConcurrentFileContainer filecon, CreateNewParam param) {
		this.filecon = filecon;
		this.param = param;
	}

	public void setTimeOut() {
	}

	/**
	 * 线程执行
	 */
	public void run() {
		while (true) {
			synchronized (this) {
				ThreadUtil.sleep(12000);
				System.out.println("該線程是否需要結束");
				// 取得文件容器中的DB文件
				ConcurrentHashMap<String, CurrentFileBean> currentFiles = filecon.getDbfiles();
				Enumeration<CurrentFileBean> beans = currentFiles.elements();
				boolean allhascurrent = true;
				while (beans.hasMoreElements()) {
					CurrentFileBean bean = beans.nextElement();
					if(!bean.isHascurrent()){
						allhascurrent = false;
						break;
					}
				}
				
				System.out.println("allhascurrent: " + allhascurrent);
				// 停止同步
				if(allhascurrent){
					ConcurrentHashMap<String, CurrentFileBean> needindex = filecon.getNeedindexfile();
					System.out.println("need index file size::" + needindex.keySet().size());
					for (Iterator iter = needindex.keySet().iterator(); iter.hasNext();) {
						String path = (String) iter.next();
						System.out.println("need reindex filepath::" + path);
					}
					try {
						IndexMaker.makeindex(param.getSelectfiletype(), param.getIdexpath(), param.getSearchname(), needindex.keySet());
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					ThreadPoolExecutor exector = ConcurrentFileThreadManager.getThreadManager().getPool();
					BlockingQueue<Runnable> tasks = exector.getQueue();
					for (Iterator iter = tasks.iterator(); iter.hasNext();) {
						ConcurrentDbIndexTask  task = (ConcurrentDbIndexTask)iter;
						CreateNewParam parm = task.getCreateNewParam();
						if(parm.equals(param)){
							task.stopthread();
						}
					}
					break;
				}
			}
		}
	}

	public CreateNewParam getParam() {
		return param;
	}

	public void setParam(CreateNewParam param) {
		this.param = param;
	}
}
