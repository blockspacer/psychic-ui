#pragma once

#include <memory>
#include "Skin.hpp"
#include "Div.hpp"

namespace psychic_ui {

    template<class T>
    class Component : public Div {
    protected:
        Component();

    public:

        const std::shared_ptr<T> skin() const { return _skin; };
        Component<T> *setSkin(std::shared_ptr<T> skin);

    protected:
        void draw(SkCanvas */*canvas*/) override {/*Skin Manages drawing*/}

        virtual void skinChanged() {}

        void styleUpdated() override;

        std::string        _skinName{};
        std::shared_ptr<T> _skin{nullptr};

        // Make some of div's stuff protected since we manage our content
        using Div::add;
        using Div::remove;
        using Div::removeAll;
    };

    template<class T>
    Component<T>::Component():
        Div() {
        setTag("Component");
        // Our skin will inherit all of our styles but the external ones (margin)
        // But we should do our part and ignore any internal layout styling
        _ignoreInternalLayoutContraints = true;
    }

    template<class T>
    Component<T> *Component<T>::setSkin(std::shared_ptr<T> skin) {
        if (skin != _skin) {
            if (_skin) {
                _skin->removedFromComponent();
                this->remove(_skin);
            }
            _skin = skin;
            if (_skin) {
                // Skin is always in the back so the component can add more
                // children if need be (ie: TextInput overlays its text)
                this->add(0, _skin);
                _skin->addedToComponent();
            }
            skinChanged();
        }
        return this;
    }

    template<class T>
    void Component<T>::styleUpdated() {
        Div::styleUpdated();
        std::string skinName = _computedStyle->get(StringProperty::skin);
        if (skinName != _skinName) {
            _skinName = skinName;
            setSkin(std::dynamic_pointer_cast<T>(styleManager()->skin(_skinName)));
        }
    }
}
