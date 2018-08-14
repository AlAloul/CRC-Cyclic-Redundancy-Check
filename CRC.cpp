#include < iostream > #include < conio.h > #include < cstdlib > #include < ctime > #define N 100

using namespace std;

class channel {
  public:
    channel(int s_): size(s_) {}
  int * error(int * , int);
  private:
    int size;
};

class receiver {
  public:
    receiver(int n): sizeFrame(n) {}
  int * copy(int * , int * , int);
  int * RFrame, * C;
  private:
    int sizeFrame;
};

class sender {
  public:
    sender(int s): C(s), R(s) {}
  void EnterSizes();
  void EnterInformations();
  void sheftLeft();
  void CopyCode();
  void division();
  void addRemainder();
  void finalFrame();
  int Fsize() {
    return frameSize;
  }
  void FrameData();
  void damageFrame();
  void copyToReceiver();
  void copyFrame();
  void divisionR();
  private:
    channel C;
  receiver R;
  int * frame, frameSize, sAddr, rAddr, sdw, scw, * data, * code, * c, nbOfFrames;
  int * divisor, sDivisor;
};

int main() {
  int NS, i;
  cout << "Enter the number of senders that they wish to use the same channel:\n";
  cin >> NS;
  cout << "\nNote that the number of receivers must be :   " << NS;
  channel Y(100);
  for (i = 0; i < NS; i++) {
    cout << "\n\n***********************************************************************";
    cout << "\nThe frame number(" << i + 1 << "):\n";
    cout << "*******************\n";
    sender X(20);
    X.EnterSizes();
    X.EnterInformations();
    X.sheftLeft();
    X.CopyCode();
    X.division();
    X.addRemainder();
    X.finalFrame();
    cout << "\nNow we want to pass through the channel !!.\n";
    X.damageFrame();
    cout << "\nReceiver Frame[" << i + 1 << "]:\n";
    X.copyToReceiver();
    X.divisionR();
  }
  getch();
  return 0;
}

void sender::copyFrame() {
  R.C = new int[frameSize - 2];
  for (int i = 1; i < frameSize - 1; i++)
    R.C[i] = R.RFrame[i];
}

void sender::copyToReceiver() {
  R.RFrame = new int[frameSize];
  R.RFrame = R.copy(R.RFrame, frame, frameSize);
  cout << "\n-------------------------\n";
  for (int i = 0; i < frameSize; i++)
    cout << R.RFrame[i] << " ";
  cout << "\n-------------------------\n";
}

int * receiver::copy(int * A, int * B, int s) {
  for (int i = 0; i < s; i++)
    A[i] = B[i];
  return A;
}

void sender::FrameData() {
  for (int i = 0; i < frameSize; i++)
    cout << frame[i];
}

void sender::damageFrame() {
  frame = C.error(frame, frameSize);
  cout << "\nThe new frame after passing through the channel is:\n";
  cout << "\n-------------------------\n";
  for (int i = 0; i < frameSize; i++)
    cout << frame[i] << " ";
  cout << "\n-------------------------\n";
}

void sender::finalFrame() {
  frame = new int[frameSize];
  int i;
  cout << "\n\nThe final frame to be send by the sender is :\n";
  cout << "(Note that the source address is the most left bit of the frame,and the destination addressis the most right bit of the frame).\n";
  frame[0] = sAddr;
  cout << "\n-------------------------\n";
  cout << frame[0];
  cout << " ";
  frame[1] = rAddr;
  cout << frame[1] << " ";
  for (i = 2; i < scw + 2; i++) {
    frame[i] = code[i - 2];
    cout << frame[i] << " ";
  }
  for (i = scw + 2; i < sDivisor + scw + 2; i++) {
    frame[i] = divisor[i - scw - 2];
    cout << frame[i] << " ";
  }

  cout << "\n-------------------------\n";
  cout << endl;
}

void sender::addRemainder() {
  int i;
  for (i = scw - sDivisor + 1; i < scw; i++)
    code[i] = c[i];
  cout << "\nThe new codeword after adding the remainder is:\n";
  cout << "\n-------------------\n";
  for (i = 0; i < scw; i++)
    cout << code[i] << " ";
  cout << "\n-------------------\n";
}

void sender::CopyCode() {
  c = new int[scw];
  for (int i = 0; i < scw; i++)
    c[i] = code[i];
}

void sender::EnterSizes() {
  cout << "\nEnter the size of dataword:\n";
  cin >> sdw;
  cout << "\nEnter the size of the divisor:\n";
  cin >> sDivisor;
  scw = sdw + sDivisor - 1;
  frameSize = scw + sDivisor + 2;
  cout << "\nNote that the size of the codeword is:  " << scw << "\nand the size of all the frame that contains of:the final codeword,the source address,the destination address,the CRC,is:  " << frameSize;
}

void sender::EnterInformations() {
  divisor = new int[sDivisor];
  data = new int[sdw];
  int i;
  cout << "\n\nEnter the data:\n";
  for (i = 0; i < sdw; i++)
    cin >> data[i];
  cout << "\nEnter the divisor:\n";
  for (i = 0; i < sDivisor; i++)
    cin >> divisor[i];
  cout << "\nEnter the address of the sender then the address of the receiver:\n";
  cin >> sAddr >> rAddr;
}

void sender::sheftLeft() {
  int i;
  code = new int[scw];
  for (i = scw - 1; i >= scw - sdw; i--)
    code[i] = 0;
  for (i = 0; i < sdw; i++)
    code[i] = data[i];
  cout << "the initial codeword after shifting and before division by g(x),(at the sender) is:\n";
  cout << "\n-------------------\n";
  for (i = 0; i < scw; i++)
    cout << code[i] << " ";
  cout << "\n-------------------\n";
}

void sender::division() {
  int i = 0, k = 0, q[10], d, j;
  while (scw - i - 1 >= sDivisor) {
    if (c[i] == 0) {
      q[k] = 0;
      for (j = i; j < (sDivisor + i); j++)
        c[j] += 0;
      k++;
      i++;
    } //end if
    if (c[i] == 1) {
      q[k] = 1;
      for (j = i, d = 0; j < sDivisor + i, d < sDivisor; j++, d++)
        c[j] = (c[j] + divisor[d]) % 2;
      k++;
      i++;
    } // end if
  } // end while
  cout << "\nthe remainder of this division is:\n";
  for (j = i + 1; j < scw; j++)
    cout << c[j];
}

/*       At the channel   :        */
int * channel::error(int * A, int size) {
  srand((unsigned) time(0));
  int random_integer;
  for (int i = 2; i < size; i++) {
    random_integer = (rand() % 2);
    A[i] = random_integer;
  }
  return A;
}

void sender::divisionR() {
  int i = 2, k = 0, q[10], d, j, sum = 0;
  while (scw + sDivisor - i + 1 >= sDivisor) {
    if (R.RFrame[i] == 0) {
      q[k] = 0;
      for (j = i; j < (sDivisor + i); j++)
        R.RFrame[j] += 0;
      k++;
      i++;
    }
    if (R.RFrame[i] == 1) {
      q[k] = 1;
      for (j = i, d = 0; j < sDivisor + i, d < sDivisor; j++, d++)
        R.RFrame[j] = (R.RFrame[j] + divisor[d]) % 2;
      k++;
      i++;
    }
  }
  cout << "\n\nthe remainder of division of the received frame by the divisor is:\n";
  for (j = i + 1; j < scw + sDivisor + 2; j++) {
    cout << R.RFrame[j];
    sum += R.RFrame[j];
  }
  if (sum == 0) {
    cout << "\nthere is no error during transmission.\n";
    cout << "Then we can extract the data from this received frame which is:\n";
    for (i = 2; i < sdw + 2; i++)
      cout << frame[i];
  } else {
    cout << "\n!! the remainder is not zero !!!!!!";
    cout << "\nthere are errors during transmission(since the remainder of division is not zero).\n";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n\t(So this data is discarded)\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  }
}