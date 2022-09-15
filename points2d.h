// --> Bhawanpreet Singh
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <cstdlib>
#define CAP 10
namespace teaching_project {

template<typename Object>
class Points2D {
  public:

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D() : capacity_(CAP), size_(0), sequence_(new std::array<Object, 2>[CAP]){
      //Declares a Points2D object with no points
    }

    // Copy-constructor.
    Points2D(const Points2D &rhs) : capacity_(rhs.capacity_), size_(rhs.size_), sequence_(nullptr){
      // Creates a new Points2D object by doing a deep copy of passed Points2D object.
      this->sequence_ = new std::array<Object, 2>[this->capacity_];
      for(int i = 0; i < this->size_; i++){
        this->sequence_[i][0] = rhs.sequence_[i][0];
        this->sequence_[i][1] = rhs.sequence_[i][1];
      }
    }

    Points2D& operator=(const Points2D &rhs){
      // Assigns passed in Object to this.
      // First it makes sure this object frees any memory it occupies
      // Then it ceates a deep copy of rhs sequence to this sequence and returns a reference to this.
      if(this != &rhs){
        delete [] this->sequence_;
        this->capacity_ = rhs.capacity_;
        this->size_ = rhs.size_;
        this->sequence_ = new std::array<Object, 2>[this->capacity_];
        for(int i = 0; i < this->size_; i++){
          this->sequence_[i][0] = rhs.sequence_[i][0];
          this->sequence_[i][1] = rhs.sequence_[i][1];
        }
      }
      return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs) : capacity_(rhs.capacity_), size_(rhs.size_), sequence_(rhs.sequence_){
      // Constructs a Points2D object from passed in r value reference.
      // The passed in object sequence is assigned to nullptr so
      // that the destructor doesnt try to free the same memory mutiple times.
      rhs.capacity_ = 0;
      rhs.size_ = 0;
      rhs.sequence_ = nullptr;
    }

    // Move-assignment.
    Points2D& operator=(Points2D &&rhs){
      // Assigns the rhs to this and this to rhs.
      if(this != & rhs){
        std::swap(this->sequence_, rhs.sequence_);
        std::swap(this->size_, rhs.size_);
        std::swap(this->capacity_, rhs.capacity_);
      }
      return *this;
    }

    ~Points2D(){
      // Frees up memmory allocated in the constructors.
      this->capacity_ = 0;
      this->size_ = 0;
      delete [] this->sequence_;
      this->sequence_ = nullptr;
    }

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) : capacity_(CAP), size_(1), sequence_(new std::array<Object, 2>[CAP]){
        // Creates a Points2D object with 1 point in the sequence.
        this->sequence_[0][0] = item[0];
        this->sequence_[0][1] = item[1];
    }

    size_t size() const {
        // Returns current size of sequence.
        return this->size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        // Returns the point from the sequence at passed in location.
        if(location >= this->size_){
          std::cerr << "ERROR\n";
          std::abort();
        }
        return this->sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
      Points2D result;
      if(c1.size_ > c2.size_){
        for(int i = 0; i < c2.size_; i++){
          if(result.size_ == result.capacity_){
            result.increaseCapacity();
          }
          result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
          result.size_++;
        }
        for(int i = c2.size_; i < c1.size_; i++){
          if(result.size_ == result.capacity_){
            result.increaseCapacity();
          }
          result.sequence_[i][0] = c1.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1];
          result.size_++;
        }
      }
      else if(c2.size_ > c1.size_){
        for(int i = 0; i < c1.size_; i++){
          if(result.size_ == result.capacity_){
            result.increaseCapacity();
          }
          result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
          result.size_++;
        }
        for(int i = c1.size_; i < c2.size_; i++){
          if(result.size_ == result.capacity_){
            result.increaseCapacity();
          }
          result.sequence_[i][0] = c2.sequence_[i][0];
          result.sequence_[i][1] = c2.sequence_[i][1];
          result.size_++;
        }
      }
      else{
        for(int i = 0; i < c1.size_; i++){
          if(result.size_ == result.capacity_){
            result.increaseCapacity();
          }
          result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
          result.size_++;
        }
      }
      return result;
    }

    // Overloading the << operator.
    // Outputs the points in the sequence, and empty parenthesis if sequence is empty.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        if(some_points.size_ == 0){
          out << "()";
        }
        for(int i = 0; i < some_points.size_; i++){
            out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ") ";
        }
        out << "\n";
        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        int numPoints;
        in >> numPoints;
        for(int i = 0; i < numPoints; i++){
          if(some_points.size_ == some_points.capacity_){
            some_points.increaseCapacity();
          }
          Object x, y;
          in >> x;
          in >> y;
          some_points.sequence_[some_points.size_][0] = x;
          some_points.sequence_[some_points.size_][1] = y;
          some_points.size_++;
        }
        return in;
    }
  private:
    // Helper method to increase Capacity of sequence
    void increaseCapacity(){
      this->capacity_ += 10;
      std::array<Object, 2> *newSequence = new std::array<Object, 2>[this->capacity_];
      for(int i = 0; i < this->size_; i++){
        newSequence[i][0] = this->sequence_[i][0];
        newSequence[i][1] = this->sequence_[i][1];
      }
      delete [] this->sequence_;
      this->sequence_ = newSequence;
    }
    // Capacity of sequence
    size_t capacity_;
    // Size of sequence.
    size_t size_;
    // Sequence of points.
    std::array<Object, 2> *sequence_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
