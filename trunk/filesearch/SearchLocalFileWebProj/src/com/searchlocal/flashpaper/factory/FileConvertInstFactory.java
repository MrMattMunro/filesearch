package com.web.searchlocal.flashpaper.factory;

import java.io.File;
import java.util.Enumeration;
import java.util.ResourceBundle;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.web.searchlocal.flashpaper.FileConvert;
import com.web.searchlocal.flashpaper.impl.FileConvert4DwgImpl;
import com.web.searchlocal.flashpaper.impl.FileConvert4SwfImpl;

/**
 * �ļ�ת��ʵ��,���ڴ�����Ӧת��ʵ��
 * @author WangYanCheng
 * @version 2009-12-3
 */
public class FileConvertInstFactory {
	
	/**logger*/
	private Log logger = null;

	/**Singleton pattern*/
	private static FileConvertInstFactory fcifObj = null;

	/**�ļ����Ŀ¼*/
	private String outputFolder4Swf = "file.swf.outputfolder",
			outputFolder4Dwg = "file.dwg.outputfolder";

	/**instance to bind properties*/
	private ResourceBundle resBoundInst = null;

	/**swf support*/
	private String[] swfFileSupport = { ".txt", ".doc", ".docx", ".pdf", ".xls", ".xlsx" };

	/**dwg support*/
	private String[] dwgFileSupport = { ".dwg" };

	/**
	 * private constructor
	 */
	private FileConvertInstFactory() {
		logger = LogFactory.getLog(this.getClass());
		//�����ⲿ�����ļ�
		resBoundInst = ResourceBundle.getBundle("com.hd.nx.doc.properties");
	}

	/**
	 * ��ȡ����ʵ��
	 * @return fcifObj
	 */
	public static final FileConvertInstFactory getInstance() {
		if (fcifObj == null) {
			fcifObj = new FileConvertInstFactory();
		}
		return fcifObj;
	}

	/**
	 * ��ȡ�ļ�ת��ʵ��
	 * 
	 * @param fileInst �ļ�ʵ��
	 * @return fileConvertInst/null
	 * @throws HDException �׳��쳣��Log
	 */
	public FileConvert getFileConvertInst(File fileInst) {
		if (null == fileInst) {
			return null;
		}
		String fileName = fileInst.getName().toLowerCase();
		FileConvert fileConvertInst = null;
		if (endWith(fileName, swfFileSupport)) {
			fileConvertInst = new FileConvert4SwfImpl();
			fileConvertInst.setOutFolder(new File(resBoundInst.getString(outputFolder4Swf)));
			String tmpCommand = resBoundInst.getString("file.swf.command");
			if (null != tmpCommand && !"".equals(tmpCommand)) {
				fileConvertInst.setCommand(tmpCommand);
			}
		} else if (endWith(fileName, dwgFileSupport)) {
			fileConvertInst = new FileConvert4DwgImpl();
			fileConvertInst.setOutFolder(new File(resBoundInst.getString(outputFolder4Dwg)));
			String tmpCommand = resBoundInst.getString("file.dwg.command");
			if (null != tmpCommand && !"".equals(tmpCommand)) {
				fileConvertInst.setCommand(tmpCommand);
			}
		} else {
			logger.error("FileConvertInstFactory->δ֪���ļ�����{@FILE_NAME@}".replaceAll("@FILE_NAME@",
					fileName));
		}
		return fileConvertInst;
	}

	/**
	 * end with
	 * @param str Դ�ַ�
	 * @param strArray �ַ�
	 * @return true/false
	 */
	private boolean endWith(String str, String[] strArray) {
		boolean result = false;
		for (String tmpStr : strArray) {
			if (str.endsWith(tmpStr)) {
				result = true;
				break;
			}
		}
		return result;
	}

	/**
	 * end with
	 * @param str Դ�ַ�
	 * @return true/false
	 */
	public boolean endWith4Swf(String str) {
		return endWith(str, swfFileSupport);
	}

	/**
	 * end with
	 * @param str Դ�ַ�
	 * @return true/false
	 */
	public boolean endWith4Dwg(String str) {
		return endWith(str, dwgFileSupport);
	}

	/**
	 * check property
	 */
	public void checkProperty() {
		Enumeration enumInst = this.resBoundInst.getKeys();
		while (enumInst.hasMoreElements()) {
			String key = (String) enumInst.nextElement();
		}
	}

	/**
	 * �������
	 * @param args �����б�
	 */
	public static void main(String[] args) {
		FileConvertInstFactory fcifInst = FileConvertInstFactory.getInstance();
		fcifInst.checkProperty();
	}
}
