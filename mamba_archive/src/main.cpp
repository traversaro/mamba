// Copyright (c) 2019, QuantStack and Mamba Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#include "archive.hpp"

#include "mamba/version.hpp"

#include "mamba/core/context.hpp"
#include "mamba/core/output.hpp"
#include "mamba/core/thread_utils.hpp"

#include "mamba/api/configuration.hpp"

#include <CLI/CLI.hpp>


int
main(int argc, char** argv)
{
    using namespace mamba;  // NOLINT(build/namespaces)

    CLI::App app{ "Version: " + version() + "\n" };
    set_archive_command(&app);

    try
    {
        CLI11_PARSE(app, argc, argv);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << e.what();
        set_sig_interrupted();
        return 1;
    }

    if (app.get_subcommands().size() == 0)
    {
        Configuration::instance().load();
        Console::print(app.help());
    }

    return 0;
}
