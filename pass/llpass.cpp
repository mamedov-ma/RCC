#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace
{

struct noPhiPass : public FunctionPass
{
  noPhiPass() : FunctionPass(ID) {}

  inline bool isFuncLogger(StringRef name)
  {
    return name == "anyOptLogger";
  }

  virtual bool runOnFunction(Function &F)
  {
    if (isFuncLogger(F.getName()))
    {
      return false;
    }

    // Dump Function
    outs() << "In a function called " << F.getName() << "\n\n";

    // Prepare builder for IR modification
    LLVMContext &Ctx = F.getContext();
    IRBuilder<> builder(Ctx);
    Type *retType = Type::getVoidTy(Ctx);

    // Prepare optLogger function
    ArrayRef<Type *> anyOptParamTypes = { builder.getInt8Ty()->getPointerTo() };
    FunctionType *anyOptLogFuncType = FunctionType::get(retType, anyOptParamTypes, false);
    FunctionCallee anyOptLogFunc = F.getParent()->getOrInsertFunction("anyOptLogger", anyOptLogFuncType);

    for (auto &B : F)
    {
      for (auto &I : B)
      {

        // Skip PHI Nodes
        if (auto *phi = dyn_cast<PHINode>(&I))
        {
          continue;
        }

        // Skip logger functions
        if (auto *call = dyn_cast<CallInst>(&I))
        {
          Function *callee = call->getCalledFunction();
          if (callee && isFuncLogger(callee->getName()))
          {
            continue;
          }
        }

        // Insert before instruction
        builder.SetInsertPoint(&I);

        // Insert a call to anyOptLogFunc function
        Value *opName = builder.CreateGlobalStringPtr(I.getOpcodeName());
        if (opName)
        {
          Value *args[] = {opName};
          builder.CreateCall(anyOptLogFunc, args);
        }
      }
    }
    return true;
  }

  static char ID;
};

} // namespace

char noPhiPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registernoPhiPass(const PassManagerBuilder &, legacy::PassManagerBase &PM)
{
  PM.add(new noPhiPass());
}

static RegisterStandardPasses RegisternoPhiPass(PassManagerBuilder::EP_OptimizerLast, registernoPhiPass);