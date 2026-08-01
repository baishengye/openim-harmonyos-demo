
import testNapi from 'libdemocpp.so';

export function add(a:number,b:number){
  testNapi.add(a,b);
}