/*
 * Copyright(C) 2010 Slfile Company, Ltd. All Rights Reserved.
 */
package com.searchlocal.thread.concurrent;

import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.ChangInfoBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.lucene.CurrentIndexUtil;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.service.ChangeInfoService;
import com.searchlocal.service.FileService;

/**
 * 同步索引对象
 *
 * @author 昌松
 * @version $Revision1.0$
 */
public class ConcurrentFileIndex {

	/**
	 * 同步索引
	 * 
	 * @param param 搜索对象
	 */
	public static void concurent(CreateNewParam param) {
		ChangeInfoService changeInfoService = new ChangeInfoService();
		FileService fileservice = new FileService();
		String namespace = param.getSearchname();
		try {
			// 取得每个待处理文件
			List<ChangInfoBean> notOperList = changeInfoService.getChangeInfoByHasoper(namespace,
					Constant.HasOperFlg.HAS_NOT_OPER);

			// 迭代每个待处理文件
			List<FileParam> fileList = new ArrayList<FileParam>();
			for (Iterator<ChangInfoBean> iter = notOperList.iterator(); iter.hasNext();) {
				// 取得待处理文件各个值
				ChangInfoBean bean = (ChangInfoBean) iter.next();
				String operflg = bean.getOperflg();
				String filepath = bean.getPath();
				long lastmodify = bean.getLastmodify();
				
				// 需要追加
				if (Constant.OperFlag.NEED_ADD.equals(operflg)) {
					// 如果文件不存在，则返回
					File file = new File(filepath);
					if(!file.exists()){
						continue;
					}
					// 新建文件对象
					FileParam element = new FileParam();
					element.setPath(filepath);
					element.setLastModify(lastmodify);
					element.setError(Constant.NO_ERROR);
					fileList.add(element);
					// 追加索引
					CurrentIndexUtil.makeIndexByPath(namespace, bean);
				}
				// 需要更新
				if (Constant.OperFlag.NEED_UPDATE.equals(operflg)) {
					// 如果文件不存在，则返回
					File file = new File(filepath);
					if(!file.exists()){
						continue;
					}
					// 对文件内容记录进行更新(先删除,后插入)
					fileservice.deleteRecord(namespace, "t_file", filepath);
					// 新建文件对象
					FileParam element = new FileParam();
					element.setPath(filepath);
					element.setLastModify(lastmodify);
					element.setError(Constant.NO_ERROR);
					fileList.add(element);
					// 删除索引
					CurrentIndexUtil.deleteDcoumentByPath(namespace, filepath);
					// 追加索引
					CurrentIndexUtil.makeIndexByPath(namespace, bean);
				}
				// 需要删除
				if (Constant.OperFlag.NEED_DEL.equals(operflg)) {
					// 删除文件记录
					fileservice.deleteRecord(namespace, "t_file", filepath);
					// 删除索引
					CurrentIndexUtil.deleteDcoumentByPath(namespace, filepath);
				}
				// 把该记录设成已经处理
				bean.setHasoper(Constant.HasOperFlg.HAS_OPER);
				changeInfoService.updateHasOper(bean, namespace);
			}
			// 写入File表(包括追加和更新)
			fileservice.insertFileRecord(fileList, namespace);
		} catch (DBException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} catch (LogicException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		}

	}
}
