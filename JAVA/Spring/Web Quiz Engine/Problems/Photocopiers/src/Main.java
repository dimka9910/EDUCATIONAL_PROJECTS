/**
 * Class to work with
 */
class Multiplicator {

	public static <T extends Copy<T>> Folder<T>[] multiply(Folder<T> folder, int arraySize) {
	    Folder<T>[] f = new Folder[arraySize];
	    for (int i = 0; i < arraySize; i++){
	        Folder<T> ff = new Folder<T>();
            ff.put(folder.get().copy());
	        f[i] = ff;
        }
	    return f;
		// Method to implement
	}
}

// Don't change the code below
interface Copy<T> {
	T copy();
}

class Folder<T> {

    private T item;

    public void put(T item) {
    	this.item = item;
    }



    public T get() {
        return this.item;
    }
}