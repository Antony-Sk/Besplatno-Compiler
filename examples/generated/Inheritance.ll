; ModuleID = 'OplLLVM'
source_filename = "OplLLVM"

%Main = type { ptr }
%B = type { %A, i64, ptr }
%A = type { i64, ptr }

@vtableMain = global [0 x ptr] zeroinitializer
@vtableA = global [1 x ptr] [ptr @setA_Integer_A_]
@vtableB = global [1 x ptr] [ptr @setA_Integer_A_]

declare i64 @Integer_()

define %Main @Main_() {
entry:
  %_tmpsetA_Integer_B_ = alloca %B, align 8
  %x = alloca %B, align 8
  %this = alloca %Main, align 8
  %this.vtableMain = getelementptr inbounds %Main, ptr %this, i32 0, i32 0
  store ptr @vtableMain, ptr %this.vtableMain, align 8
  %calltmp = call %B @B_Integer_Integer_(i64 1, i64 2)
  store %B %calltmp, ptr %x, align 8
  %x1 = load %B, ptr %x, align 8
  store %B %x1, ptr %_tmpsetA_Integer_B_, align 8
  %_tmpsetA_Integer_B_.vtableB = getelementptr inbounds %B, ptr %_tmpsetA_Integer_B_, i32 0, i32 2
  %0 = load ptr, ptr %_tmpsetA_Integer_B_.vtableB, align 8
  %1 = getelementptr inbounds [1 x ptr], ptr %0, i32 0, i32 0
  %setA_Integer_B_ = load ptr, ptr %1, align 8
  %2 = load %B, ptr %_tmpsetA_Integer_B_, align 8
  %calltmp2 = call i64 %setA_Integer_B_(i64 5, %B %2)
  %3 = load %Main, ptr %this, align 8
  ret %Main %3
}

define %B @B_Integer_Integer_(i64 %x, i64 %y) {
entry:
  %this = alloca %B, align 8
  %y2 = alloca i64, align 8
  %x1 = alloca i64, align 8
  store i64 %x, ptr %x1, align 4
  store i64 %y, ptr %y2, align 4
  %0 = call %A @A_()
  %this.b = getelementptr inbounds %B, ptr %this, i32 0, i32 1
  %calltmp = call i64 @Integer_()
  store i64 %calltmp, ptr %this.b, align 4
  %this.vtableB = getelementptr inbounds %B, ptr %this, i32 0, i32 2
  store ptr @vtableB, ptr %this.vtableB, align 8
  %this.a = getelementptr inbounds %A, ptr %this, i32 0, i32 0
  %x3 = load i64, ptr %x1, align 4
  store i64 %x3, ptr %this.a, align 4
  %this.b4 = getelementptr inbounds %B, ptr %this, i32 0, i32 1
  %y5 = load i64, ptr %y2, align 4
  store i64 %y5, ptr %this.b4, align 4
  %1 = load %B, ptr %this, align 8
  ret %B %1
}

define i64 @setA_Integer_A_(i64 %v, ptr %this) {
entry:
  %this2 = alloca ptr, align 8
  %v1 = alloca i64, align 8
  store i64 %v, ptr %v1, align 4
  store ptr %this, ptr %this2, align 8
  %this.a = getelementptr inbounds %A, ptr %this2, i32 0, i32 0
  %v3 = load i64, ptr %v1, align 4
  store i64 %v3, ptr %this.a, align 4
  %this.a4 = getelementptr inbounds %A, ptr %this2, i32 0, i32 0
  %a = load i64, ptr %this.a4, align 4
  ret i64 %a
}

define %A @A_() {
entry:
  %this = alloca %A, align 8
  %this.a = getelementptr inbounds %A, ptr %this, i32 0, i32 0
  %calltmp = call i64 @Integer_()
  store i64 %calltmp, ptr %this.a, align 4
  %this.vtableA = getelementptr inbounds %A, ptr %this, i32 0, i32 1
  store ptr @vtableA, ptr %this.vtableA, align 8
  %0 = load %A, ptr %this, align 8
  ret %A %0
}

define i32 @main() {
entry:
  %0 = call %Main @Main_()
  ret i32 0
}
