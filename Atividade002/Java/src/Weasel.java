import java.util.HashMap;
import java.util.Random;

public class Weasel {

    public Weasel(){}

    public void run() {
        Random random = new Random();
        char[] characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
        char[] target = "METHINKS IT IS LIKE A WEASEL".toCharArray();
        char[][] wordList = copy(characters,random);
        char[] bestFromGen = pickBest(wordList,target);
        System.out.println("GEN 1 " + String.valueOf(bestFromGen));
        if(String.valueOf(bestFromGen).equals(String.valueOf(target))){
            System.out.println("MATCH " + String.valueOf(bestFromGen));
        }
        else{
            int gen = 2;
            Boolean match = false;

            while(!(match)){

                System.out.println("GEN " + String.valueOf(gen) + " " + String.valueOf(bestFromGen));

                wordList = copyBest(random,bestFromGen,characters);
                bestFromGen = pickBest(wordList,target);
                if(String.valueOf(bestFromGen).equals(String.valueOf(target))){
                    System.out.println("GEN " + String.valueOf(gen) + " " + String.valueOf(bestFromGen) + " | MATCH!!!");
                    match = true;
                }
                else{
                    gen++;
                }
            }
        }
    }
    public char[][] copy(char[] charList, Random rand){
        char[][] wordList = new char[100][28];

        for(int i = 0; i < 100; i++){
            char[] word = mutateWord(rand,generateRandom(charList,rand),charList);
            wordList[i] = word;
        }
        return wordList;
    }

    public char[] mutateWord(Random rand,char[] word, char[] characters){
        for(int i = 0; i < word.length; i++) {
            if (rand.nextFloat() > 0.94) {
                word[i] = characters[rand.nextInt(26)];
            }
        }
        return word;
    }

    public char[] generateRandom(char[] charList, Random rand){
        char[] word = new char[28];
        for(int i = 0; i < 28; i++){
            word[i] = charList[rand.nextInt((26))];
        }
        return word;
    }

    public char[] pickBest(char[][] wordList, char[] target){
        int score = 0;
        char[] winner = null;
        for(char[] word : wordList){
            HashMap<Integer,char[]> hm = (compare(word,target));
            for (Integer key : hm.keySet() ) {
                if (key > score) {
                    score = key;
                    winner = hm.get(key);
                }
            }
        }
        return winner;
    }

    public HashMap compare(char[] word, char[] target){
        HashMap<Integer, char[]> hm = new HashMap<>();
        int score = 0;
        for(int i = 0; i < 28; i++){
            if(word[i] == target[i]){
                score = score + 1;
            }
        }
        hm.put(score,word);
        return hm;
    }

    public char[][] copyBest(Random randNum, char[] best, char[] characters){
        String copyBest = String.valueOf(best);
        char[][] wordList = new char[100][28];
        for(int i = 0; i < 100; i++){
            char[] word = mutateWord(randNum,copyBest.toCharArray(),characters);
            wordList[i] = word;
        }
        return wordList;
    }
}