package com.web.searchlocal.flashpaper.impl;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.web.searchlocal.flashpaper.FileConvert;

/**
 * �ļ�ת��dwg��ʽ֧��
 * 
 * <p>Title: �ļ�ת��dwg��ʽ֧��</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileConvert4DwgImpl implements FileConvert {

	/**ת����ɺ���ļ����*/
	private File fileInst = null;

	/**���Ŀ¼*/
	private File outFolder = null;

	/**default command*/
	private String defaultCommand = "AcmeCADConverter.exe";

	/**
	 * {@inheritDoc}
	 */
	public File doConvertFile(File inputFileInst, File outputFileInst) {
		new InnerConvertThread(inputFileInst, outputFileInst);
		return fileInst;
	}

	/**
	 * {@inheritDoc}
	 */
	public File doConvertFile(File inputFileInst) {
		new InnerConvertThread(inputFileInst, null);
		return fileInst;
	}

	/**
	 * {@inheritDoc}
	 */
	public void setOutFolder(File setOutFolder) {
		this.outFolder = setOutFolder;
	}

	/**
	 * InnerConvert
	 * @author WangYanCheng
	 * @version 2009-12-4
	 */
	class InnerConvertThread implements Runnable {
		/**inputFile*/
		private File inFile = null;

		/**outFilePath*/
		private File outFile = new File(System.getProperty("java.io.tmpdir"));

		/**
		 * Constructor
		 * @param inFileObj inFileObj
		 * @param outFilePath outFilePath
		 */
		public InnerConvertThread(File inFileObj, File outFilePath) {
			this.inFile = inFileObj;
			this.outFile = outFilePath == null ? outFolder : outFilePath;
			Thread th = new Thread(this);
			th.start();
		}

		/**
		 * Constructor
		 * @param setInFile input file to set
		 * @param setOutFolder output Folder to set
		 */
		public InnerConvertThread(String setInFile, String setOutFolder) {
			this.inFile = new File(setInFile);
			this.outFile = null == setOutFolder ? outFolder : this.outFile;
			new InnerConvertThread(inFile, outFile);
		}

		/**
		 * {@inheritDoc}
		 */
		public void run() {
			String tmpOutFile = outFile.getPath().concat(File.separator).concat(
					inFile.getName().replaceAll("[.]{1}.*$", ".svgz"));
			fileInst = new File(tmpOutFile);
			List<String> commandList = new ArrayList<String>();
			commandList.add(defaultCommand);
			commandList.add("/r");
			commandList.add("/e");
			commandList.add("/f");
			commandList.add("106");
			commandList.add("/d");
			commandList.add(outFile.getPath());
			commandList.add(inFile.getPath());
			commandList.add("/a");
			commandList.add("0");
			ProcessBuilder pbObj = new ProcessBuilder();
			pbObj.command(commandList);
			Map<String, String> envMap = pbObj.environment();
			envMap.clear();
			envMap.putAll(System.getenv());
			pbObj.directory(outFile);
			pbObj.redirectErrorStream(true);
			try {
				Process proObj = pbObj.start();
				final InputStream ins = proObj.getInputStream();
				final ByteBuffer byteBuffer = ByteBuffer.allocate(1024);
				Thread th = new Thread() {
					public void run() {
						ReadableByteChannel rbcObj = Channels.newChannel(ins);
						try {
							while (rbcObj.read(byteBuffer) != -1) {
								byteBuffer.flip();
								logger.info(java.nio.charset.Charset.defaultCharset().decode(
										byteBuffer));
								byteBuffer.clear();
							}
						} catch (IOException e) {
							logger.error(e);
						}
					}
				};
				th.setDaemon(true);
				th.start();
				try {
					proObj.waitFor();
					proObj.destroy();
					logger.info("ת�����.".concat(tmpOutFile));
				} catch (InterruptedException e) {
					logger.error(e);
				}
			} catch (IOException e) {
				logger.error(e);
			}
		}
	}

	/**
	 * {@inheritDoc}
	 */
	public String getCommand() {
		return defaultCommand;
	}

	/**
	 * {@inheritDoc}
	 */
	public void setCommand(String tmpCommand) {
		this.defaultCommand = tmpCommand;
	}

	/**logger instance*/
	private Log logger = LogFactory.getLog(FileConvert4DwgImpl.class);

	/**
	 * �������
	 * @param args �����б�
	 */
	public static void main(String[] args) {
		File inputFileInst = new File("F:\\tools\\flex\\dwg\\0009HDAA2-89.dwg"), outputFileInst = new File(
				"D:\\work\\workspace\\HDEAM_NXSH\\pro\\docReader\\svgzFile\\");
		FileConvert4DwgImpl fc4Di = new FileConvert4DwgImpl();
		fc4Di.doConvertFile(inputFileInst, outputFileInst);
	}
}
