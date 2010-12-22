package com.searchlocal.convertswf;

import java.io.File;

import jp.ne.so_net.ga2.no_ji.jcom.IDispatch;
import jp.ne.so_net.ga2.no_ji.jcom.ReleaseManager;

import com.searchlocal.util.Escape;
import com.searchlocal.util.StringUtil;

/**
 * 将文档转换成SWF文件
 */
public class Doc2Flash {

	/**
	 * 将文档转换成SWF文件
	 * 
	 * @param filepath 文件目录
	 * @param indexpath 索引目录
	 */
	public static String convert2Flash(String filepath, String swfFilePath) {

		ReleaseManager rm = new ReleaseManager();
		try {
			// Create Server object
			IDispatch p2f = new IDispatch(rm, "Print2Flash3.Server");

			// Setup interface and protection options
			IDispatch defProfile = (IDispatch) p2f.get("DefaultProfile");
//			defProfile.put("InterfaceOptions", P2FConst.INTLOGO | P2FConst.INTZOOMSLIDER
//					| P2FConst.INTPREVPAGE | P2FConst.INTGOTOPAGE | P2FConst.INTNEXTPAGE
//					| P2FConst.INTSEARCHBOX | P2FConst.INTSEARCHBUT | P2FConst.INTROTATE
//					| P2FConst.INTPRINT | P2FConst.INTNEWWIND | P2FConst.INTHELP
//					| P2FConst.INTBACKBUTTON | P2FConst.INTBACKBUTTONAUTO
//					| P2FConst.INTFORWARDBUTTON | P2FConst.INTFORWARDBUTTONAUTO);
			
			defProfile.put("InterfaceOptions", P2FConst.INTZOOMSLIDER
			| P2FConst.INTPREVPAGE | P2FConst.INTGOTOPAGE | P2FConst.INTNEXTPAGE
			| P2FConst.INTSEARCHBOX | P2FConst.INTSEARCHBUT);
		
			defProfile.put("ProtectionOptions", P2FConst.PROTDISPRINT | P2FConst.PROTENAPI
					| P2FConst.PROTENAPI);

			// 文件名形式 eg：E_tasklist1.xlsx_20100904223127.swf
			// 全路径文件名_YYYYMMDDHHSSMM.swf
			String swfFileName = StringUtil.getSwfFileName(filepath);
			swfFileName = Escape.escape(swfFileName);
			swfFileName = swfFileName.replaceAll("%u", "");
			
			String tempPath = swfFilePath + File.separator + swfFileName;
			File swfFile = new File(tempPath);

			// 判断swfFile是否存在
			if (!swfFile.exists()) {
				// 不存在的场合
				// 参数设置
				Object[] param = new Object[] { filepath, tempPath, new String("/FormName:Letter"), 
						new String("/Orientation:2") };
				p2f.method("ConvertFile", param);
				System.out.println("Conversion completed successfully");
			} 
			// 删除掉以前修改多次的而生成的SWF文件
			String temp = swfFileName.substring(0, swfFileName.length()-18);
			File indxDir = new File(swfFilePath);
			File[] files = indxDir.listFiles();
			for(int i=0; i< files.length ; i++){
				File file = files[i];
				String fileName = file.getName();
				if(file.isFile() && fileName.indexOf(temp) != -1 && ! fileName.equals(swfFileName)){
					file.delete();
				}
			}
			return swfFileName;
		} catch (Exception e) {
			
			// TODO
			System.out.println("An error occurred at conversion: " + e.toString());
		}  finally {
			rm.release();
		}
		return null;
	}

	public static void main(String[] args) {
		Doc2Flash doc2flash = new Doc2Flash();
		String filepath = "E:\\tasklist1.xlsx";
		String idexpath = "F:\\index";
//		String idexpath = args[0];
//		String filepath = args[1];
		doc2flash.convert2Flash(filepath, idexpath);
	}
}
