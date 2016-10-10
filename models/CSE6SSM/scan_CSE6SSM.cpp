// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Wed 3 Jun 2015 23:53:01

#include "CSE6SSM_two_scale_input_parameters.hpp"
#include "CSE6SSM_spectrum_generator.hpp"
#include "CSE6SSM_two_scale_model_slha.hpp"

#include "command_line_options.hpp"
#include "scan.hpp"
#include "lowe.h"
#include "logger.hpp"

#include <iostream>
#include <cstring>

namespace flexiblesusy {

void print_usage()
{
   std::cout <<
      "Usage: scan_CSE6SSM.x [options]\n"
      "Options:\n"
      "  --m0=<value>\n"
      "  --m12=<value>\n"
      "  --TanBeta=<value>\n"
      "  --SignLambdax=<value>\n"
      "  --Azero=<value>\n"
      "  --sInput=<value>\n"
      "  --QSInput=<value>\n"
      "  --SigmaLInput=<value>\n"
      "  --KappaPrInput=<value>\n"
      "  --SigmaxInput=<value>\n"
      "  --MuPrInput=<value>\n"
      "  --MuPhiInput=<value>\n"
      "  --BMuPrInput=<value>\n"
      "  --BMuPhiInput=<value>\n"

      "  --help,-h                         print this help message"
             << std::endl;
}

void set_command_line_parameters(int argc, char* argv[],
                                 CSE6SSM_input_parameters<Two_scale>& input)
{
   for (int i = 1; i < argc; ++i) {
      const char* option = argv[i];

      if(Command_line_options::get_parameter_value(option, "--m0=", input.m0))
         continue;

      if(Command_line_options::get_parameter_value(option, "--m12=", input.m12))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TanBeta=", input.TanBeta))
         continue;

      if(Command_line_options::get_parameter_value(option, "--SignLambdax=", input.SignLambdax))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Azero=", input.Azero))
         continue;

      if(Command_line_options::get_parameter_value(option, "--sInput=", input.sInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--QSInput=", input.QSInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--SigmaLInput=", input.SigmaLInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--KappaPrInput=", input.KappaPrInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--SigmaxInput=", input.SigmaxInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--MuPrInput=", input.MuPrInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--MuPhiInput=", input.MuPhiInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--BMuPrInput=", input.BMuPrInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--BMuPhiInput=", input.BMuPhiInput))
         continue;

      
      if (strcmp(option,"--help") == 0 || strcmp(option,"-h") == 0) {
         print_usage();
         exit(EXIT_SUCCESS);
      }

      ERROR("Unrecognized command line option: " << option);
      exit(EXIT_FAILURE);
   }
}

} // namespace flexiblesusy


int main(int argc, char* argv[])
{
   using namespace flexiblesusy;
   using namespace softsusy;
   typedef Two_scale algorithm_type;

   CSE6SSM_input_parameters<algorithm_type> input;
   set_command_line_parameters(argc, argv, input);

   QedQcd oneset;
   oneset.toMz();

   CSE6SSM_spectrum_generator<algorithm_type> spectrum_generator;
   spectrum_generator.set_precision_goal(1.0e-4);
   spectrum_generator.set_max_iterations(0);         // 0 == automatic
   spectrum_generator.set_calculate_sm_masses(0);    // 0 == no
   spectrum_generator.set_parameter_output_scale(0); // 0 == susy scale

   const std::vector<double> range(float_range(0., 100., 10));

   cout << "# "
        << std::setw(12) << std::left << "m0" << ' '
        << std::setw(12) << std::left << "Mhh(0)/GeV" << ' '
        << std::setw(12) << std::left << "error"
        << '\n';

   for (std::vector<double>::const_iterator it = range.begin(),
           end = range.end(); it != end; ++it) {
      input.m0 = *it;

      spectrum_generator.run(oneset, input);

      const CSE6SSM_slha<algorithm_type> model(spectrum_generator.get_model());
      const CSE6SSM_physical& pole_masses = model.get_physical_slha();
      const Problems<CSE6SSM_info::NUMBER_OF_PARTICLES>& problems
         = spectrum_generator.get_problems();
      const double higgs = pole_masses.Mhh(0);
      const bool error = problems.have_problem();

      cout << "  "
           << std::setw(12) << std::left << input.m0 << ' '
           << std::setw(12) << std::left << higgs << ' '
           << std::setw(12) << std::left << error;
      if (error) {
         cout << "\t# " << problems;
      }
      cout << '\n';
   }

   return 0;
}