import java.io.*;
import java.util.*;


public class LegacyCodeInputValidator {

	public static void main(String[] args) throws Exception{
		new LegacyCodeInputValidator().run();
	
	}

	void run() throws Exception{
			try{
				LegacyCodeTestCase forTest=readTestCaseFromInput();
		                if(!forTest.isConsistent()){
					System.out.println("Testcase is not consistent");
					System.exit(3);
				}
		                System.out.println("Testcase is OK");
				System.exit(42);//everything OK
			}
			catch(LegacyCodeException ex){
				System.out.println("Exception: "+ex);
				System.exit(2);
			}
	}

//reading test case:
LegacyCodeTestCase readTestCaseFromInput() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  return readTestCaseFromReader(reader);
	}
	
	
 LegacyCodeTestCase readTestCaseFromReader(BufferedReader reader) throws Exception{
		int N=Integer.parseInt(reader.readLine());
		LegacyCodeTestCase testCase=new LegacyCodeTestCase(N);
		for(int i=0;i<N;i++){
			String[] firstLine=reader.readLine().split(" ");
			String[] secondLine=reader.readLine().split(" ");
			
			if(firstLine.length!=2)
				throw new LegacyCodeException("Wrong format in the first line of the "+i+". method describtion");
			
			Method method=new Method(firstLine[0]);
			
			int k=Integer.parseInt(firstLine[1]);
			
			if(k==0 && (secondLine.length!=1 || !secondLine[0].isEmpty()))
				throw new LegacyCodeException("Expected emty line but found "+Arrays.toString(secondLine));
			
			if(k>0){
				if( k!=secondLine.length)
					throw new LegacyCodeException("Wrong number of users in the "+i+". method describtion, expected "+k+" methods but found "+secondLine.length);
			
				for(String user:secondLine)
					method.addUser(user);
			}
			
			testCase.addMethod(method);
		}
		
		testEOFLine(reader);
		
		return testCase;
	}
	
 private void testEOFLine(BufferedReader reader) throws LegacyCodeException, IOException{
		String nextLine=reader.readLine();
		 if(nextLine!=null)
			 throw new LegacyCodeException("Expected eof but found ["+nextLine+"]");
	}

//testcase:

public class LegacyCodeTestCase {
	
	public static final int N_MAX=400;
	private int N;
	private int result;
	private String testCaseName;
	
	public void setTestCaseName(String newName){
		testCaseName=newName;
	}
	
	public String getTestCaseName(){
		return testCaseName;
	}
	
	Map<MethodName, Method> methods;
	Set<MethodName> known;
	
	LegacyCodeTestCase(int n) throws LegacyCodeException{
		result=-1;
		testCaseName="";
		if(n<1 || n>N_MAX)
			throw new LegacyCodeException(n+" must be between 1 and "+N_MAX);
		
		this.N=n;
		methods=new HashMap<MethodName, Method>();
		known=new HashSet<MethodName>();
	}
	
	public void addMethod(Method method) throws LegacyCodeException{
		
		if(methods.containsKey(method.getMethodName()))
			throw new LegacyCodeException("Method "+method.getMethodName()+" already known");
		
		methods.put(method.getMethodName(), method);
		
		known.add(method.getMethodName());
		method.flushUserNames(known);
	}
	
	public boolean isConsistent(){
		return N==methods.size() && N==known.size();
	}
	
	
	public int getN(){
		return N;
	}
	
	public int getResult(){
		return result;
	}
	
	public void setResult(int newResult){
		result=newResult;
	}
	
	private Set<String> convertMethodNamesToStrings(Set<MethodName> methodNames){
		Set<String> result=new HashSet<String>();
		for(MethodName mn:methodNames)
			result.add(mn.getName());
		return result;
	}
	
	
	public Set<String> getMethodNames(){
		return convertMethodNamesToStrings(methods.keySet());
	}
	
	public Set<String> getUserNames(String name) throws LegacyCodeException{
		
		Method method=methods.get(new MethodName(name));
		if(method==null)
			throw new LegacyCodeException("No information about method with name :"+name);
		
		Set<MethodName> userNames=new HashSet<MethodName>();
		method.flushUserNames(userNames);
		
		return convertMethodNamesToStrings(userNames);
	}
	
	
	public void flushToPrinter(PrintWriter printer){
		printer.println(getN());
		for(Map.Entry<MethodName, Method> entry: methods.entrySet()){
			int k=entry.getValue().getUserCnt();
			printer.println(entry.getKey()+" "+k);
			entry.getValue().flushUserNamesToPrinter(printer);
			printer.println();
		}
	}
	

}


public class Method {
	
	private MethodName name;
	
	private Set<MethodName> users;
	
	public Method(MethodName name){
		this.name=name;
		users=new HashSet<MethodName>();
	}
	
	public Method(String name) throws LegacyCodeException{
		this(new MethodName(name));
	}
	
	public void addUser(MethodName user) throws LegacyCodeException{
		if(! users.add(user))
			throw new LegacyCodeException("User "+user+" is already in the user set");
	}
	
	public void addUser(String user) throws LegacyCodeException{
		addUser(new MethodName(user));
	}

    public MethodName getMethodName(){
    	return name;
    }
    
    public int getUserCnt(){
    	return users.size();
    }
    
    
    public void flushUserNames(Set<MethodName> nameSet){
    	for(MethodName name: users)
    		nameSet.add(name);
    }
    
    public void flushUserNamesToPrinter(PrintWriter printer){
	int cnt=0;
    	for(MethodName name: users){
    		printer.print(name);
		cnt++;
		if(cnt!=users.size())
			printer.print(" ");
	}
    }
}



public class MethodName {

	private String name;
	public  static final int MAX_LITERAL_LENGTH=20;
	
	private boolean incorrect(String literal){
		if(literal.length()==0 || literal.length()>MAX_LITERAL_LENGTH)
			 return true;
		String shouldBeEmpty=literal.replaceAll("[a-z,0-9,A-Z]", "");
		return !shouldBeEmpty.isEmpty();
	}
	

	
    public MethodName(String name) throws LegacyCodeException{
    	if(name.endsWith("::"))
    		throw new LegacyCodeException("Method name "+name +" has wrong format: ends with ::");
    	
    	String[] splitted=name.split("::");

    	if (splitted.length!=2)
    		throw new LegacyCodeException("Method name "+name +" has wrong format: false number of ::");
    	
    	if(incorrect(splitted[0]) )
    		throw new LegacyCodeException("Method name "+splitted[0]+" in "+name+" is a incorrect literal");
    	
    	 if( incorrect(splitted[1]) )
    		 throw new LegacyCodeException("Method name "+splitted[1]+" in "+name+" is a incorrect literal");
    	 
    	 
    	this.name=name;
    }
    
    @Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}



	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		MethodName other = (MethodName) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}



	public String getName(){
    	return name;
    }



	@Override
	public String toString() {
		return name;
	}
	
}


@SuppressWarnings("serial")
public class LegacyCodeException extends Exception{
	public LegacyCodeException(String what){
		super(what);
	}
}

	
}
