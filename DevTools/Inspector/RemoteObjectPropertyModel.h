/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/JsonPath.h>
#include <AK/JsonValue.h>
#include <AK/NonnullOwnPtrVector.h>
#include <LibGUI/Model.h>

namespace Inspector {

class RemoteObject;

class RemoteObjectPropertyModel final : public GUI::Model {
public:
    virtual ~RemoteObjectPropertyModel() override { }
    static NonnullRefPtr<RemoteObjectPropertyModel> create(RemoteObject& object)
    {
        return adopt(*new RemoteObjectPropertyModel(object));
    }

    enum Column {
        Name,
        Value,
        __Count,
    };

    virtual int row_count(const GUI::ModelIndex& = GUI::ModelIndex()) const override;
    virtual int column_count(const GUI::ModelIndex& = GUI::ModelIndex()) const override { return Column::__Count; }
    virtual String column_name(int) const override;
    virtual GUI::Variant data(const GUI::ModelIndex&, GUI::ModelRole) const override;
    virtual void set_data(const GUI::ModelIndex&, const GUI::Variant&) override;
    virtual void update() override;
    virtual bool is_editable(const GUI::ModelIndex& index) const override { return index.column() == Column::Value; }
    virtual GUI::ModelIndex index(int row, int column, const GUI::ModelIndex& parent = GUI::ModelIndex()) const override;
    virtual GUI::ModelIndex parent_index(const GUI::ModelIndex&) const override;

private:
    explicit RemoteObjectPropertyModel(RemoteObject&);

    const JsonPath* cached_path_at(int n, const Vector<JsonPathElement>& prefix) const;
    const JsonPath* find_cached_path(const Vector<JsonPathElement>& path) const;

    RemoteObject& m_object;
    mutable NonnullOwnPtrVector<JsonPath> m_paths;
};

}
