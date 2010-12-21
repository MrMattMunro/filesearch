package com.searchlocal.thread.concurrent;

import java.util.ArrayList;
import java.util.List;

import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.XMLConfig;

/**
 * 同步文件与数据库任务
 * 
 * <p>Title: 同步文件与数据库任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentFile {
	
	/**
	 * 同步方法
	 */
	public static void listen() {
	
		// 取得搜索信息
		XMLConfig xmlconfig = new XMLConfig();
		List<CreateNewParam> searches = xmlconfig.getEntityList();
	
		// 保证一个搜索对象有一个同步线程
		// directory作为零界资源，只能被一个对象获得，故一个directory只能有一个IndexWriter被打开
		// 开始同步DB和索引
		List<ConcurrentFileContainer> containList = new ArrayList<ConcurrentFileContainer>();
		for (int i = 0; i < searches.size(); i++) {
			// 文件容器
			ConcurrentFileContainer filecon = new ConcurrentFileContainer();
			filecon.setSearchList(searches.subList(i, i+1));
			
			CreateNewParam createNewParam = searches.get(i);
			ConcurrentDbIndexTask concurrentDbIndexTask = new ConcurrentDbIndexTask();
			concurrentDbIndexTask.init(filecon, createNewParam);
			
			// 向文件容器放入文件
			ConcurrentPutFilePathTask putFilePathTask = new ConcurrentPutFilePathTask();
			putFilePathTask.init(filecon);
			
			// 监控是否停止同步文件
			StopConcurrentTask stopConcurrentTask = new StopConcurrentTask();
			stopConcurrentTask.init(filecon, createNewParam);
			// 加入所有容器
			containList.add(filecon);
			
			// 开始检索DB文件
			BaseConcurrentThreadManager.getThreadManager().executeThread(putFilePathTask);
			// 开始执行
			ConcurrentFileThreadManager.getThreadManager().executeThread(concurrentDbIndexTask);
			// 监控停止搜索的时间
			BaseConcurrentThreadManager.getThreadManager().executeThread(stopConcurrentTask);
		}
		ExitConcurrentTask exitTask = new ExitConcurrentTask();
		exitTask.init(containList);
		// 开始执行
		ConcurrentFileThreadManager.getThreadManager().executeThread(exitTask);
		
	}
}
