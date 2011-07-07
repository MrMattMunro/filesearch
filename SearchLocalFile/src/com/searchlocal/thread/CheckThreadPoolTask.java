package com.searchlocal.thread;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ThreadPoolExecutor;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.service.FileService;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.util.MenuMessageUtil;

public class CheckThreadPoolTask extends CRunnable {

	private CreateNewParam param;

	private FileContainer filecon;

	private static boolean isdone = false;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public void init(CreateNewParam param, FileContainer filecon) {
		this.param = param;
		this.filecon = filecon;
	}

	public void run() {
		while (true) {
			try {
				Thread.sleep(10000);
				if (this.filecon.isIsdone() || isdone) {
					continue;
				}
				ThreadPoolExecutor pool = ThreadCheckThreadManager.getThreadManager().getPool();

				synchronized (this) {
					int allfilenum = filecon.getAllfile().size();
					int haserrfilenum = filecon.getHaserrorfile().size();
					int insertfilenum = filecon.getInsertedfile().size();
					System.out.println("FileContainer.getAllfile():" + allfilenum);
					System.out.println("FileContainer.getHaserrorfile():" + haserrfilenum);
					System.out.println("FileContainer.getInsertedfile():" + insertfilenum);
					int activecount = pool.getActiveCount();
					if (allfilenum == 0 && activecount == 1) {

						List<FileParam> filebeanList = new ArrayList<FileParam>();

						// has error file
						ConcurrentHashMap<String, Long> haserrorfile = filecon.getHaserrorfile();
						Set<String> keyset = haserrorfile.keySet();
						for (Iterator iter = keyset.iterator(); iter.hasNext();) {
							String path = (String) iter.next();
							FileParam param = filecon.gethaserrorfile(path);
							param.setError(Constant.HAS_ERROR);
							filebeanList.add(param);
						}

						// inserted file
						ConcurrentHashMap<String, Long> insertfile = filecon.getInsertedfile();
						Set<String> insertkeyset = insertfile.keySet();
						for (Iterator iter = insertkeyset.iterator(); iter.hasNext();) {
							String path = (String) iter.next();
							FileParam param = filecon.getinsertedfile(path);
							param.setError(Constant.NO_ERROR);
							filebeanList.add(param);
						}
						
						// insert File Bean
						FileService fileService = new FileService();
						fileService.insertFileRecord(filebeanList, param.getSearchname());

						// 清空資源
						filebeanList.clear();
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
	 * @return the filecon
	 */
	public FileContainer getFilecon() {
		return filecon;
	}

	/**
	 * @param filecon the filecon to set
	 */
	public void setFilecon(FileContainer filecon) {
		this.filecon = filecon;
	}

	/**
	 * @return the isdone
	 */
	public static boolean isIsdone() {
		return isdone;
	}

	/**
	 * @param isdone the isdone to set
	 */
	public static void setIsdone(boolean isdone) {
		CheckThreadPoolTask.isdone = isdone;
	}
}
