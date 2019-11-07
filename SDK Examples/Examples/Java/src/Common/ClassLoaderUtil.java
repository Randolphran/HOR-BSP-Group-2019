package Common;

import java.net.MalformedURLException;

public class ClassLoaderUtil {
	
     public static ClassLoader getClassLoader() {
        return ClassLoaderUtil.class.getClassLoader();
     }
    
     public static String getAbsolutePathOfClassLoaderClassPath(){
         return ClassLoaderUtil.getClassLoader().getResource("").toString();        
     }
    
     public static String getExtendResource(String relativePath) throws MalformedURLException{
         String classPathAbsolutePath=ClassLoaderUtil.getAbsolutePathOfClassLoaderClassPath();
         if(relativePath.substring(0, 1).equals("/")){
             relativePath=relativePath.substring(1);
         }
       
         String wildcardString=relativePath.substring(0,relativePath.lastIndexOf("../")+3);
         relativePath=relativePath.substring(relativePath.lastIndexOf("../")+3);
         int containSum=ClassLoaderUtil.containSum(wildcardString, "../");
         classPathAbsolutePath= ClassLoaderUtil.cutLastString(classPathAbsolutePath, "/", containSum);
         String resourceAbsolutePath=classPathAbsolutePath+relativePath;
         return resourceAbsolutePath;
     }
    
     private static int containSum(String source,String dest){
         int containSum=0;
         int destLength=dest.length();
         while(source.contains(dest)){
             containSum=containSum+1;
             source=source.substring(destLength); 
         }
         return containSum;
     }
    
     private static String cutLastString(String source,String dest,int num){
         for(int i=0;i<num;i++){
             source=source.substring(0, source.lastIndexOf(dest, source.length()-2)+1);      
         }         
         return source;
     }
}