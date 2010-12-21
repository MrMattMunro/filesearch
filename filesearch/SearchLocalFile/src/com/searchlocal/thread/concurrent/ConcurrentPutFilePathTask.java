package com.searchlocal.thread.concurrent;

import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.CurrentFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.service.FileService;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;

/**
 * 向文件容器里放入文件任务
 * 
 * <p>Title: 同步文件任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentPutFilePathTask extends CRunnable {

	/** 文件容器 */
	private ConcurrentFileContainer filecon;

	/**
	 * 初期化操作
	 * 
	 * @param filecon 文件容器
	 */
	public void init(ConcurrentFileContainer filecon) {
		this.filecon = filecon;
	}

	/**
	 * 过期函数
	 */
	public void setTimeOut() {
	}

	
	public void run() {
		
		while (true) {
			synchronized (this) {
				int dbfilenum = filecon.getDbfiles().size();
				if (dbfilenum == 0) {
					filecon.setAbletoStart(false);
					List<CreateNewParam> searches = filecon.getSearchList();
					if (searches.size() == 0) {
				        ThreadUtil.wait(this);
					}
					System.out.println("searches size:" + searches.size());
					FileService fileservice = new FileService();
					for (Iterator<CreateNewParam> iter = searches.iterator(); iter.hasNext();) {
						CreateNewParam element = (CreateNewParam) iter.next();
						try {
							List<FileParam> beanList = fileservice.getFileRecordList(element.getSearchname());
							for (Iterator<FileParam> iterator = beanList.iterator(); iterator.hasNext();) {
								FileParam param = (FileParam) iterator.next();
								CurrentFileBean bean = new CurrentFileBean();
								bean.setHascurrent(false);
								bean.setLastmodify(param.getLastModify());
								filecon.putdbfile(param.getPath(), bean);
							}
						} catch (DBException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (LogicException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					System.out.println("filecon.getDbfiles().size()"+ filecon.getDbfiles().size());
					filecon.setAbletoStart(true);
				}
			}
		}
	}
}
