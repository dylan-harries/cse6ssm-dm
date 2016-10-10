
#ifndef CMSSM_SEMI_TWO_SCALE_CONVERGENCE_TESTER_H
#define CMSSM_SEMI_TWO_SCALE_CONVERGENCE_TESTER_H

#include "CMSSM_semi_convergence_tester.hpp"
#include "CMSSM_semi_two_scale_model.hpp"
#include "two_scale_convergence_tester_drbar.hpp"

namespace flexiblesusy {

class Two_scale;

template<>
class CMSSM_semianalytic_convergence_tester<Two_scale> : public Convergence_tester_DRbar<CMSSM_semianalytic<Two_scale> > {
public:
   CMSSM_semianalytic_convergence_tester(CMSSM_semianalytic<Two_scale>*, double);
   virtual ~CMSSM_semianalytic_convergence_tester();

protected:
   virtual double max_rel_diff() const;
};

} // namespace flexiblesusy

#endif